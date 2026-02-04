#include "miniRT.h"

/**
 * @brief 	addition of two vectors
 *
 * @param 	a first vector
 * @param 	b second vector
 * @return t_vec3 the sum of the two vectors
 */
t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

/**
 * @brief 	subtraction of two vectors
 *
 * @param 	a first vector
 * @param 	b second vector
 * @return t_vec3 the difference of the two vectors
 *
 * @note 	Point – Point = Vector		→ the displacement (direction + distance) from one point to another.
 *			Vector – Vector = Vector	→ standard component-wise subtraction.
 *			Point – Vector = Point 		→ moving a point backwards along a vector.
 */
t_vec3	vec_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

/**
 * @brief 	scaling a vector by a scalar value: only modify the length
 *
 * @param 	a vector to be scaled
 * @param 	scalar value to scale by
 * @return t_vec3 the scaled vector
 *
 * @note	Vector × Scalar = Vector	→ scaling the length of a vector by a scalar value.
 * 			If the scalar is negative, the direction is reversed
			if the scalar is greater than 0, the direction is always the same
 */
t_vec3	vec_scale(t_vec3 a, float scalar)
{
	t_vec3	result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	result.z = a.z * scalar;
	return (result);
}

/**
 * @brief 	calculate the length of a vector
 *
 * @param 	a vector
 * @return float the length of the vector
 */
float	vec_len(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}
