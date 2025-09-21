#include "miniRT.h"

t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vec3	vec_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

//if the scalar is greater than 0, the direction is always the same
//only modify the length
t_vec3	vec_scale(t_vec3 a, float scalar)
{
	t_vec3	result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	result.z = a.z * scalar;
	return (result);
}

float	vec_len(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

//A vector that has length = 1 but keeps the same direction
//normalizing a vector means dividing the vector by its length
//in many calculations (lighting, direction, angles),
//we care about direction only — not length.
t_vec3	vec_normalize(t_vec3 v)
{
	float	length;

	length = vec_len(v);
	if (length == 0)
		return ((t_vec3){0, 0, 0});
	return (vec_scale(v, 1.0 / length));
}

///how much two vectors point in the same direction
//Vectors>0 point in similar direction
//Vectors=0 are perpendicular (90°)
//Vectors<0 point in opposite directions
float	vec_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

//Returns a new vector that is: Perpendicular to both a and b
t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}
