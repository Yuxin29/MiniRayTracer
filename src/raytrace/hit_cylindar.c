#include "miniRT.h"
#include "raytrace.h"


/*
Ray equation:P(t) = O + tD
cylinder equation: ||(p−C)−[(p−C)⋅V]V||² = r²
C is the center of the cylinder (usually its midpoint)
V is the axis direction (unit vector)
r is the radius
p is the point on the ray (i.e., P(t) = O + tD)
(p - C) is the vector from the cylinder center to the point.
[(p - C) ⋅ V]V is the projection onto the axis.
Let: oc = O - C
so:
(p−C)=(O+tD−C)=oc+tD
[(p - C) ⋅ V]V = [(oc+tD)⋅V]V
so:
||(oc+tD)−[(oc⋅V)+t(D⋅V)]V||² = r²
(oc+tD)−[(oc⋅V)+t(D⋅V)]V = [oc−(oc⋅V)V]+t[D−(D⋅V)V]
so let's define:
oc_perp = oc - dot(oc, V) * V;
D_perp  = D - dot(D, V) * V;
then the expression becomes:
t²(Dperp​⋅Dperp​)+2t(ocperp​⋅Dperp​)+(ocperp​⋅ocperp​)=r2
so:
A = dot(D_perp, D_perp);
B = 2 * dot(oc_perp, D_perp);
C = dot(oc_perp, oc_perp) - r^2;

float projection = vec_dot(hit_vec, cy->cy_axis);
projection gives you how far along the axis the hit point lies

*/
bool	hit_cylinder_body(t_ray ray, t_cylinder *cy, t_hit_record *rec)
{
	t_hit_info	hit;
	t_vec3	oc_prep;
	t_vec3	d_prep;
	float	t1;
	float	t2;
	float	projection;
	t_vec3	hit_vec;
	t_vec3	hit_point;

	hit.oc = vec_sub(ray.origin, cy->cy_center);
	oc_prep = vec_sub(hit.oc, vec_scale(cy->cy_axis, vec_dot(hit.oc, cy->cy_axis)));
	d_prep = vec_sub(ray.direction, vec_scale(cy->cy_axis, vec_dot(ray.direction, cy->cy_axis)));
	hit.a = vec_dot(d_prep, d_prep);
	hit.b = 2.0f * vec_dot(oc_prep, d_prep);
	hit.c = vec_dot(oc_prep, oc_prep) - cy->radius * cy->radius;
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
	hit_point = vec_add(ray.origin, vec_scale(ray.direction, hit.t));
	hit_vec = vec_sub(hit_point, cy->cy_center);
	projection = vec_doc(hit_vec, cy->cy_axis);
	if (projection > cy->height / 2.0f || projection < -cy->height / 2.0f)
		return (false);
	rec->t = hit.t;


}

/*
A cylinder is not infinitely long — it has a top cap and a bottom cap, and the valid hit region is between them.
top_center = cy_center + (axis * (height / 2))
bottom_center = cy_center - (axis * (height / 2))
*/
bool	hit_cylinder_cap(t_ray ray, t_cylinder *cy, t_hit_record *rec)
{
	t_vec3	top_cen;
	t_vec3	bottom_cen;

	top_cen = vec_add(cy->cy_center, vec_scale(cy->cy_axis, cy->height / 2.0f));
	bottom_cen = vec_sub(cy->cy_center,  vec_scale(cy->cy_axis, cy->height / 2.0f));
}
