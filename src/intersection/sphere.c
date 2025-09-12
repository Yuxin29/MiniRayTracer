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
	float	a;
	float	b;
	float	c;
	t_vec3	oc;
	float	discriminant;
	float	t;

	oc = vec_sub(ray.origin, ray.direction);
	a = vec_doc(ray.direction, ray.direction);
	b = 2.0 * vec_doc(oc, ray.direction);
	c = vec_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t < 0)
		return (false);
	rec->t = t;
	rec->point = ray_at(ray, t);
	rec->normal = vec_normalize(vec_sub(rec->point, sphere->sp_center));
	return (true);
}
