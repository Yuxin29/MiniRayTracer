#include "miniRT.h"
#include "parsing.h"

//Mathematically: P(t)=origin+t⋅direction
//why? :  we need to find “where” a ray hits something, this function calculates that point.
//A ray is a half-infinite line in 3D space, starting from a point and going in a direction.
t_vec3	ray_at(t_ray a, float t)
{
	return (vec_add(a.origin, vec_scale(a.direction, t)));
}
