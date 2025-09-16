#include "miniRT.h"
#include "parsing.h"

/*
Ray equation:P(t) = O + tD
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
	t_sphere_hit_info	hit;
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
	if (t1 > 0)
		hit.t = t1;
	else if (t2 > 0)
		hit.t = t2;
	else
		return (false);
	rec->t = hit.t;
	rec->point = ray_at(ray, hit.t);
	rec->normal = vec_normalize(vec_sub(rec->point, sphere->sp_center));
	return (true);
}
