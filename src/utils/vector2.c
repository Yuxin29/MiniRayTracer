#include "miniRT.h"

/**
 * @brief 	change a vector to a unit vector ( length = 1, direction same )
 *
 * @param 	v vector to be normalized
 * @return t_vec3 the normalized vector
 *
 * @note	if the length of the vector is 0, return (0,0,0)
			in many calculations (lighting, direction, angles),
			we care about direction only — not length.
 */
t_vec3	vec_normalize(t_vec3 v)
{
	float	length;

	length = vec_len(v);
	if (length == 0)
		return ((t_vec3){0, 0, 0});
	return (vec_scale(v, 1.0 / length));
	//normalizing a vector means dividing the vector by its length
}

/**
 * @brief 	show how much two vectors point in the same direction
 *
 * @param 	a first vector
 * @param 	b second vector
 * @return float the dot product of the two vectors
 *
 * @note	Vectors>0 point in similar direction
			Vectors=0 are perpendicular (90°)
			Vectors<0 point in opposite directions
 */
float	vec_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/**
 * @brief 	get a vector perpendicular to both input vectors
 *
 * @param 	a first vector
 * @param 	b second vector
 * @return a new vector that is: Perpendicular to both a and b
 *
 * @note	perpendicular means 90° angle between vectors
			so the cross product is a vector that is perpendicular to both input vectors
			its direction is determined by the right-hand rule
 */
t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}
