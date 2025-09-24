#include "miniRT.h"

t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}
/*
Subtraction rules
1.Point – Point = Vector
→ the displacement (direction + distance) from one point to another.
Example: B - A gives the vector from A to B.
2.Vector – Vector = Vector
→ standard component-wise subtraction.
Example: (1,2,3) - (0,1,1) = (1,1,2).
3.Point – Vector = Point
→ moving a point backwards along a vector.
*/
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
