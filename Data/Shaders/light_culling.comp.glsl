#version 450

uniform sampler2D depthMap;
uniform mat4 inverseProj;
uniform uint numLights;

#define POINT_LIGHT 0
#define SPOT_LIGHT 1
#define DIRECTIONAL_LIGHT 2

struct Light
{
    vec4  PositionWS;
    vec4  DirectionWS;
    vec4  PositionVS;
    vec4  DirectionVS;
    vec4  Color;
    float SpotlightAngle;
    float Range;
    float Intensity;
    bool  Enabled;
    bool  Selected;
    uint  Type;
    vec2  Padding;
};

struct Plane {
	vec3 N; // Normal
	float d; // Distance to origin
};

struct Frustum {
	Plane planes[4];	
};

layout(binding = 0) readonly buffer LightBuffer {
	Light data[];
} Lights;

layout(binding = 1) readonly buffer FrustumBuffer {
	Frustum data[];
} in_Frustums;

layout(binding = 2) writeonly buffer OpaqueLightGrid {
	uvec2 data[];
} o_LightGrid;

layout(binding = 3) writeonly buffer TransparentLightGrid {
	uvec2 data[];
} t_LightGrid;

layout(binding = 4) writeonly buffer OpaqueLightIndexList {
	uint data[];
} o_LightIndexList;

layout(binding = 5) writeonly buffer TransparentLightIndexList {
	uint data[];
} t_LightIndexList;

layout(binding = 6) buffer OpaqueLightIndexCounter {
	uint data[];
} o_LightIndexCounter;

layout(binding = 7) buffer TransparentLightIndexCounter {
	uint data[];
} t_LightIndexCounter;

shared uint uMinDepth;
shared uint uMaxDepth;
shared Frustum GroupFrustum;


// Opaque geometry light lists.
shared uint o_LightCount;
shared uint o_LightIndexStartOffset;
shared uint o_LightList[1024];
 
// Transparent geometry light lists.
shared uint t_LightCount;
shared uint t_LightIndexStartOffset;
shared uint t_LightList[1024];



struct Sphere 
{
	vec3 c;
	float r;	
};

bool SphereInsidePlane( Sphere sphere, Plane plane )
{
    return dot( plane.N, sphere.c ) - plane.d < -sphere.r;
}

bool SphereInsideFrustum( Sphere sphere, Frustum frustum, float zNear, float zFar )
{
    bool result = true;
 
    // First check depth
    // Note: Here, the view vector points in the -Z axis so the 
    // far depth value will be approaching -infinity.
    if ( sphere.c.z - sphere.r > zNear || sphere.c.z + sphere.r < zFar )
    {
        result = false;
    }
 
    // Then check frustum planes
    for ( int i = 0; i < 4 && result; i++ )
    {
        if ( SphereInsidePlane( sphere, frustum.planes[i] ) )
        {
            result = false;
        }
    }
 
    return result;
}

struct Cone
{
    vec3 T;   // Cone tip.
    float h;   // Height of the cone.
    vec3 d;   // Direction of the cone.
    float r;   // bottom radius of the cone.
};


bool PointInsidePlane( vec3 p, Plane plane )
{
    return dot( plane.N, p ) - plane.d < 0;
}

bool ConeInsidePlane( Cone cone, Plane plane )
{
    // Compute the farthest point on the end of the cone to the positive space of the plane.
    vec3 m = cross( cross( plane.N, cone.d ), cone.d );
    vec3 Q = cone.T + cone.d * cone.h - m * cone.r;
 
    // The cone is in the negative halfspace of the plane if both
    // the tip of the cone and the farthest point on the end of the cone to the 
    // positive halfspace of the plane are both inside the negative halfspace 
    // of the plane.
    return PointInsidePlane( cone.T, plane ) && PointInsidePlane( Q, plane );
}

bool ConeInsideFrustum( Cone cone, Frustum frustum, float zNear, float zFar )
{
    bool result = true;
 
    Plane nearPlane = { vec3( 0, 0, -1 ), -zNear };
    Plane farPlane = { vec3( 0, 0, 1 ), zFar };
 
    // First check the near and far clipping planes.
    if ( ConeInsidePlane( cone, nearPlane ) || ConeInsidePlane( cone, farPlane ) )
    {
        result = false;
    }
 
    // Then check frustum planes
    for ( int i = 0; i < 4 && result; i++ )
    {
        if ( ConeInsidePlane( cone, frustum.planes[i] ) )
        {
            result = false;
        }
    }
 
    return result;
}

// Add the light to the visible light list for opaque geometry.
void o_AppendLight( uint lightIndex )
{
    uint index = atomicAdd( o_LightCount, 1 );
    if ( index < 1024 )
    {
        o_LightList[index] = lightIndex;
    }
}
 
// Add the light to the visible light list for transparent geometry.
void t_AppendLight( uint lightIndex )
{
    uint index = atomicAdd( t_LightCount, 1 );
    if ( index < 1024 )
    {
        t_LightList[index] = lightIndex;
    }
}

vec4 ClipToView( vec4 clip )
{
    // View space position.
    vec4 view = inverseProj * clip;
    // Perspective projection.
    view = view / view.w;
 
    return view;
}


#define TILE_SIZE 16
layout(local_size_x = TILE_SIZE, local_size_y = TILE_SIZE, local_size_z = 1) in;
void main() {
	// Calculate min & max depth in threadgroup / tile.
    vec2 texCoord = gl_GlobalInvocationID.xy;
    float fDepth = texture(depthMap, texCoord).r;
    uint uDepth = floatBitsToUint( fDepth );

	if (gl_LocalInvocationIndex == 0) // Avoid contention by other threads in the group.
	{
	    uMinDepth = 0xFFFFFFFF;
	    uMaxDepth = 0;
	    o_LightCount = 0;
	    t_LightCount = 0;
	    GroupFrustum = in_Frustums.data[gl_WorkGroupID.x + ( gl_WorkGroupID.y * gl_NumWorkGroups.x )];
	}
 
	barrier();

	atomicMin(uMinDepth, uDepth);
	atomicMax(uMaxDepth, uDepth);

	barrier();

	float fMinDepth = uintBitsToFloat( uMinDepth );
	float fMaxDepth = uintBitsToFloat( uMaxDepth );
	 
	// Convert depth values to view space.
	float minDepthVS = ClipToView( vec4( 0, 0, fMinDepth, 1 ) ).z;
	float maxDepthVS = ClipToView( vec4( 0, 0, fMaxDepth, 1 ) ).z;
	float nearClipVS = ClipToView( vec4( 0, 0, 0, 1 ) ).z;
	 
	// Clipping plane for minimum depth value 
	// (used for testing lights within the bounds of opaque geometry).
	Plane minPlane = { vec3( 0, 0, -1 ), -minDepthVS };

	for ( uint i = gl_LocalInvocationIndex; i < numLights; i += TILE_SIZE * TILE_SIZE )
	{
	    if ( Lights.data[i].Enabled )
	    {
	        Light light = Lights.data[i];

			switch ( light.Type )
			{
			case POINT_LIGHT:
			{
			    Sphere sphere = { light.PositionVS.xyz, light.Range };
			    if ( SphereInsideFrustum( sphere, GroupFrustum, nearClipVS, maxDepthVS ) )
			    {
			        // Add light to light list for transparent geometry.
			        t_AppendLight( i );
			 
			        //if ( !SphereInsidePlane( sphere, minPlane ) )
			        {
			            // Add light to light list for opaque geometry.
			            o_AppendLight( i );
			        }
			    }
			}
			break;
			case SPOT_LIGHT:
			{
			    float coneRadius = tan( radians( light.SpotlightAngle ) ) * light.Range;
			    Cone cone = { light.PositionVS.xyz, light.Range, light.DirectionVS.xyz, coneRadius };
			    if ( ConeInsideFrustum( cone, GroupFrustum, nearClipVS, maxDepthVS ) )
			    {
			        // Add light to light list for transparent geometry.
			        t_AppendLight( i );
			 
			        if ( !ConeInsidePlane( cone, minPlane ) )
			        {
			            // Add light to light list for opaque geometry.
			            o_AppendLight( i );
			        }
			    }
			}
			break;
			case DIRECTIONAL_LIGHT:
	        {
	            // Directional lights always get added to our light list.
	            // (Hopefully there are not too many directional lights!)
	            t_AppendLight( i );
	            o_AppendLight( i );
	        }
	        break;
	        }
    	}
	}
	barrier();

	// Update global memory with visible light buffer.
	// First update the light grid (only thread 0 in group needs to do this)
	if ( gl_LocalInvocationIndex == 0 )
	{
		// Update light grid for opaque geometry.
		o_LightIndexStartOffset = atomicAdd( o_LightIndexCounter.data[0], o_LightCount );
		o_LightGrid.data[gl_WorkGroupID.x + ( gl_WorkGroupID.y * gl_NumWorkGroups.x )] = uvec2( o_LightIndexStartOffset, o_LightCount );
	 
		// Update light grid for transparent geometry.
		t_LightIndexStartOffset = atomicAdd( t_LightIndexCounter.data[0], t_LightCount );
		t_LightGrid.data[gl_WorkGroupID.x + ( gl_WorkGroupID.y * gl_NumWorkGroups.x )] = uvec2( t_LightIndexStartOffset, t_LightCount );
	}
	barrier();

	for ( uint i = gl_LocalInvocationIndex; i < o_LightCount; i += TILE_SIZE * TILE_SIZE )
	{
	    o_LightIndexList.data[o_LightIndexStartOffset + i] = o_LightList[i];
	}
	// For transparent geometry.
	for ( uint i = gl_LocalInvocationIndex; i < t_LightCount; i += TILE_SIZE * TILE_SIZE )
	{
	    t_LightIndexList.data[t_LightIndexStartOffset + i] = t_LightList[i];
	}
}




