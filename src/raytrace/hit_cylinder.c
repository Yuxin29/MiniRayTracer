#include "miniRT.h"

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
line77: >0 inside ray, so flip-> outside
*/
bool	compute_cylinder_body_hit(t_hit_cy_info *hit, t_ray ray, t_cylinder *cy)
{
	float	t1;
	float	t2;

	hit->oc = vec_sub(ray.origin, cy->cy_center);
	hit->oc_prep = vec_sub(hit->oc,
			vec_scale(cy->cy_axis, vec_dot(hit->oc, cy->cy_axis)));
	hit->d_prep = vec_sub(ray.direction,
			vec_scale(cy->cy_axis, vec_dot(ray.direction, cy->cy_axis)));
	hit->a = vec_dot(hit->d_prep, hit->d_prep);
	hit->b = 2.0f * vec_dot(hit->oc_prep, hit->d_prep);
	hit->c = vec_dot(hit->oc_prep, hit->oc_prep) - cy->radius * cy->radius;
	hit->discriminant = hit->b * hit->b - 4 * hit->a * hit->c;
	if (hit->discriminant < 0)
		return (false);
	t1 = (-hit->b - sqrt(hit->discriminant)) / (2.0f * hit->a);
	t2 = (-hit->b + sqrt(hit->discriminant)) / (2.0f * hit->a);
	if (t1 > EPSILON && t2 > EPSILON)
		hit->t = fmin(t1, t2);
	else if (t1 > EPSILON)
		hit->t = t1;
	else if (t2 > EPSILON)
		hit->t = t2;
	else
		return (false);
	return (true);
}

static bool	hit_cylinder_body(t_ray ray, t_cylinder *cy, t_hit_record *rec)
{
	t_hit_cy_info	hit;

	if (!compute_cylinder_body_hit(&hit, ray, cy))
		return (false);
	hit.hit_point = vec_add(ray.origin, vec_scale(ray.direction, hit.t));
	hit.hit_vec = vec_sub(hit.hit_point, cy->cy_center);
	hit.projection = vec_dot(hit.hit_vec, cy->cy_axis);
	if (hit.projection > cy->height / 2.0f
		|| hit.projection < -cy->height / 2.0f)
		return (false);
	hit.projected = vec_add(cy->cy_center,
			vec_scale(cy->cy_axis, hit.projection));
	rec->normal = vec_normalize(vec_sub(hit.hit_point, hit.projected));
	if (vec_dot(ray.direction, rec->normal) > 0)
		rec->normal = vec_scale(rec->normal, -1);
	rec->t = hit.t;
	rec->point = hit.hit_point;
	return (true);
}

static bool	hit_cylinder_caps(t_ray ray, t_cylinder *cy,
	t_hit_record *rec)
{
	t_hit_record	rec_top;
	t_hit_record	rec_bot;
	bool			hit_top;
	bool			hit_bot;

	hit_top = hit_top_cap(ray, cy, &rec_top);
	hit_bot = hit_bottom_cap(ray, cy, &rec_bot);
	if (hit_top && (!hit_bot || rec_top.t < rec_bot.t))
	{
		*rec = rec_top;
		return (true);
	}
	else if (hit_bot)
	{
		*rec = rec_bot;
		return (true);
	}
	return (false);
}

bool	hit_cylinder(t_ray ray, t_cylinder *cy, t_hit_record *rec)
{
	t_hit_record	body_hit;
	t_hit_record	cap_hit;
	bool			body;
	bool			caps;

	body = hit_cylinder_body(ray, cy, &body_hit);
	caps = hit_cylinder_caps(ray, cy, &cap_hit);
	if (body && (!caps || body_hit.t < cap_hit.t))
	{
		*rec = body_hit;
		return (true);
	}
	else if (caps)
	{
		*rec = cap_hit;
		return (true);
	}
	return (false);
}
