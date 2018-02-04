#version 450


//uniform vec2 screenDimensions;
//uniform mat4 inverseProj;

uniform sampler2D depthMap;

layout(binding = 0) buffer FrustumBuffer {
	Frustum data[];
} out_Frustums;



struct Plane {
	vec3 N; // Normal
	float d; // Distance to origin
};

struct Frustum {
	Plane planes[4];	
};

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


bool PointInsidePlane( vec p, Plane plane )
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


