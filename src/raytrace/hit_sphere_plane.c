#include "miniRT.h"
#include "parsing.h"

/*
Ray equation:P(t) = O + tD
why? :  we need to find “where” a ray hits something, this function calculates that point.
A ray is a half-infinite line in 3D space, starting from a point and going in a direction.

Sphere equation (center C, radius r): ||P(t) - C||² = r²
Substitute the ray into the sphere equation:||O + tD - C||² = r²
Simplify: Let: oc = O - C
Then: ||oc + tD||² = r²
Expand the square using dot product:
So:
(oc + tD) ⋅ (oc + tD) = r²
Use distributive property of dot product:
oc ⋅ oc + 2t(oc ⋅ D) + t²(D ⋅ D) = r²
Rearranged form:
Bring everything to one side to form a quadratic:
t²(D ⋅ D) + 2t(oc ⋅ D) + (oc ⋅ oc - r²) = 0
This is a quadratic equation of the form:
at² + bt + c = 0
Where:
a = D ⋅ D, (vec_dot(D, D))
b = 2 * (oc ⋅ D),(2*vec_dot())
c = oc ⋅ oc - r² , (vec_dot（）- r²)

t represents how far along the ray we go to reach the hit point.
The smaller t usually hits the closest point on the object.
The larger t might hit the back of the object (or go through it).
We want the first visible intersection — the front of the object.
*/
bool	hit_sphere(t_ray ray, t_sphere *sphere, t_hit_record *rec)
{
	t_hit_info	hit;
	float	t1;
	float	t2;

	hit.oc = vec_sub(ray.origin, sphere->sp_center);
	hit.a = vec_dot(ray.direction, ray.direction);
	hit.b = 2.0f * vec_dot(hit.oc, ray.direction);
	hit.c = vec_dot(hit.oc, hit.oc) - sphere->radius * sphere->radius;
	hit.discriminant = hit.b * hit.b - 4 * hit.a * hit.c;
	if (hit.discriminant < 0)
		return (false);
	t1 = (-hit.b - sqrt(hit.discriminant)) / (2.0f * hit.a);
	t2 = (-hit.b + sqrt(hit.discriminant)) / (2.0f * hit.a);
	if (t1 > EPSILON) //?
		hit.t = t1;
	else if (t2 > EPSILON)
		hit.t = t2;
	else
		return (false);
	rec->t = hit.t;
	rec->point = vec_add(ray.origin, vec_scale(ray.direction, rec->t));
	rec->normal = vec_normalize(vec_sub(rec->point, sphere->sp_center));
	return (true);
}

//yuxin needs to write
// typedef struct s_ray
// {
// 	t_vec3	origin;
// 	t_vec3	direction;;
// }	t_ray;
// typedef struct s_hit_record
// {
// 	float	t; //t represents how far along the ray we go to reach the hit point.
// 	t_vec3	point; //hit point
// 	t_vec3	normal; //A normal is a vector that points perpendicular to the surface at a specific point.
// 	t_color	rgb; //0916modify
// }	t_hit_record;
// float	vec_dot(t_vec3 a, t_vec3 b)
// {
// 	return (a.x * b.x + a.y * b.y + a.z * b.z);
// }
// t_vec3	vec_add(t_vec3 a, t_vec3 b);
// t_vec3	vec_sub(t_vec3 a, t_vec3 b);
// t_vec3	vec_scale(t_vec3 a, float scalar);
// float	vec_len(t_vec3 a);
// t_vec3	vec_normalize(t_vec3 v);
// float	vec_dot(t_vec3 a, t_vec3 b);
// t_vec3	vec_cross(t_vec3 a, t_vec3 b);
bool	hit_plane(t_ray ray, t_plane *plane, t_hit_record *rec)
{
	float				don;

	don = vec_dot(plane->nor_v, ray.direction);
	if (don == 0) // if (fabs(den) < 1e - 6), 1e-6 =（0.000001）
		return (false);
	rec->rgb = plane->rgb;
	rec->t = vec_dot(vec_sub(plane->p_in_pl, ray.origin), plane->nor_v) / don; // how fa
	if (rec->t < 0)
		return (false);
	rec->point = vec_add(ray.origin, vec_scale(ray.direction, rec->t));
	if (vec_dot(ray.direction, plane->nor_v) < 0)
        rec->normal = plane->nor_v;
    else
	{
		rec->normal = vec_scale(plane->nor_v, -1);
	}
	return (true);
}
