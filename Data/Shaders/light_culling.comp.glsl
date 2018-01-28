#version 450

struct Plane
{
	vec3 N; // Normal
	float d; // Distance to origin
};

Plane ComputePlane(vec3 p0, vec3 p1, vec3 p2)
{
	Plane plane;
	vec3 v0 = p1 - p0;
	vec3 v2 = p2 - p0;

	plane.N = normalize(cross(v0, v2));
	plane.d = dot(plane.N, p0);

	return plane;
}