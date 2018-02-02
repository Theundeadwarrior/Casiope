#version 450

#define TILE_SIZE 16

struct Plane {
	vec3 N; // Normal
	float d; // Distance to origin
};

struct Frustum {
	Plane planes[4];	
};



uniform vec2 screenDimensions;
uniform mat4 inverseProj;

layout(binding = 0) buffer FrustumBuffer {
	Frustum data[];
} out_Frustums;




Plane ComputePlane(vec3 p0, vec3 p1, vec3 p2) {
	Plane plane;
	vec3 v0 = p1 - p0;
	vec3 v2 = p2 - p0;

	plane.N = normalize(cross(v0, v2));
	plane.d = dot(plane.N, p0);

	return plane;
}

//struct ComputeShaderInput {
//	uvec3 groupId; // gl_WorkGroupID
//	uvec3 groupThreadId; // gl_LocalInvocationID
//	uvec3 dispatchThreadId; // gl_GlobalInvocationID
//	uint groupIndex; // gl_LocalInvocationIndex
//};


vec4 ClipToView( vec4 clip )
{
    // View space position.
    vec4 view = inverseProj * clip;
    // Perspective projection.
    view = view / view.w;
 
    return view;
}

vec4 ScreenToView(vec4 screen)
{
	// Convert to normalized texture coordinates
    vec2 texCoord = screen.xy / screenDimensions;
 
    // Convert to clip space
    vec4 clip = vec4( vec2( texCoord.x, 1.0f - texCoord.y ) * 2.0f - 1.0f, screen.z, screen.w );
 
    return ClipToView( clip );
}


#define TILE_SIZE 16
layout(local_size_x = TILE_SIZE, local_size_y = TILE_SIZE, local_size_z = 1) in;
void main() {
	const vec3 eyePos = vec3( 0, 0, 0 );

	vec4 screenSpace[4];

	// Top left point
	screenSpace[0] = vec4( gl_GlobalInvocationID.xy * TILE_SIZE, -1.0f, 1.0f );
    // Top right point
    screenSpace[1] = vec4( vec2( gl_GlobalInvocationID.x + 1, gl_GlobalInvocationID.y ) * TILE_SIZE, -1.0f, 1.0f );
    // Bottom left point
    screenSpace[2] = vec4( vec2( gl_GlobalInvocationID.x, gl_GlobalInvocationID.y + 1 ) * TILE_SIZE, -1.0f, 1.0f );
    // Bottom right point
    screenSpace[3] = vec4( vec2( gl_GlobalInvocationID.x + 1, gl_GlobalInvocationID.y + 1 ) * TILE_SIZE, -1.0f, 1.0f );

	vec3 viewSpace[4];
	// Now convert the screen space points to view space
	for ( int i = 0; i < 4; i++ )
	{
	    viewSpace[i] = ScreenToView( screenSpace[i] ).xyz;
	}

	Frustum frustum;
	// Left plane
	frustum.planes[0] = ComputePlane( eyePos, viewSpace[2], viewSpace[0] );
	// Right plane
	frustum.planes[1] = ComputePlane( eyePos, viewSpace[1], viewSpace[3] );
	// Top plane
	frustum.planes[2] = ComputePlane( eyePos, viewSpace[0], viewSpace[1] );
	// Bottom plane
	frustum.planes[3] = ComputePlane( eyePos, viewSpace[3], viewSpace[2] );

    // Store the computed frustum in global memory (if our thread ID is in bounds of the grid).
    if ( gl_GlobalInvocationID.x < TILE_SIZE && gl_GlobalInvocationID.y < TILE_SIZE )
    {
        uint index = gl_GlobalInvocationID.x + ( gl_GlobalInvocationID.y * TILE_SIZE );
        out_Frustums.data[index] = frustum;
    }
}
