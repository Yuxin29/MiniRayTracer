#include "miniRT.h"

/**
 * @brief 	the ray-sphere intersection function called in rendering scene
 *
 * @param 	ray ray to be checked for intersection
 * @param 	*sphere sphere to be checked for intersection
 * @param 	*rec hit record to store intersection info	
 * @return 	bool indicating if there was a hit
 *
 * @note 	Ray equation:P(t) = O + tD
			why? :  we need to find “where” a ray hits something,
			this function calculates that point.
			A ray is a half-infinite line in 3D space, starting
			from a point and going in a direction.
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
 *
 */
bool	hit_sphere(t_ray ray, t_sphere *sphere, t_hit_record *rec)
{
	t_hit_sphere_info	hit;

	hit.oc = vec_sub(ray.origin, sphere->sp_center);
	hit.a = vec_dot(ray.direction, ray.direction);
	hit.b = 2.0f * vec_dot(hit.oc, ray.direction);
	hit.c = vec_dot(hit.oc, hit.oc) - sphere->radius * sphere->radius;
	hit.discriminant = hit.b * hit.b - 4 * hit.a * hit.c;
	if (hit.discriminant < 0)
		return (false);
	hit.t1 = (-hit.b - sqrt(hit.discriminant)) / (2.0f * hit.a);
	hit.t2 = (-hit.b + sqrt(hit.discriminant)) / (2.0f * hit.a);
	if (hit.t1 > EPSILON && hit.t2 > EPSILON)
		hit.real_t = fmin(hit.t1, hit.t2);
	else if (hit.t1 > EPSILON)
		hit.real_t = hit.t1;
	else if (hit.t2 > EPSILON)
		hit.real_t = hit.t2;
	else
		return (false);
	rec->t = hit.real_t;
	rec->point = vec_add(ray.origin, vec_scale(ray.direction, rec->t));
	rec->normal = vec_normalize(vec_sub(rec->point, sphere->sp_center));
	if (vec_dot(ray.direction, rec->normal) > 0)
		rec->normal = vec_scale(rec->normal, -1);
	return (true);
}



/**
 * @brief 	the ray-sphere intersection function called in rendering scene
 *
 * @param 	ray ray to be checked for intersection
 * @param 	*sphere sphere to be checked for intersection
 * @param 	*rec hit record to store intersection info	
 * @return 	void
 *
 * @note 	first check if plane is horizontal to ray,
			if yes, not hit
			don: denominator: fenmu
			rec->t: t= (Po​−O)⋅n​ / d⋅n
			if (rec->t < EPSILON): ray towards the back directions
			P=O+t⋅Drsection — the front of the object.
 */
bool	hit_plane(t_ray ray, t_plane *plane, t_hit_record *rec)
{
	float	don;

	don = vec_dot(plane->nor_v, ray.direction);
	if (fabs(don) < EPSILON)
		return (false);
	rec->t = vec_dot(vec_sub(plane->p_in_pl, ray.origin), plane->nor_v) / don;
	if (rec->t < EPSILON)
		return (false);
	rec->point = vec_add(ray.origin, vec_scale(ray.direction, rec->t));
	if (vec_dot(ray.direction, plane->nor_v) < 0)
		rec->normal = plane->nor_v;
	else
		rec->normal = vec_scale(plane->nor_v, -1);
	return (true);
}
