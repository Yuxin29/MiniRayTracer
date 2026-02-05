#include "miniRT.h"

/**
 * @brief 	check if a point is in shadow relative to a light source
 *
 * @param 	ray shadow ray from the point towards the light source
 * @param 	*obj object list in the scene
 * @param 	max_len distance to the light source
 * @return 	void
 * @note 	Ray equation:P(t) = O + tD
			if t < light_len, ensures the object blocks the path to the light.
			light_len = light_pos - hit_pos,
			shadow_ray:
			shadow_origin = rec.p + rec.normal * EPSILON;
			shadow Direction = light dir = normalized(light_position - hit_point);
			how can i get t then?
			using hit_something by shadow ray;
 */
static bool	hit_shadow(t_ray ray, t_object *obj, float max_len)
{
	t_hit_record	tmp;

	while (obj)
	{
		if (obj->type == OBJ_SP && hit_sphere(ray, (t_sphere *)obj->data, &tmp))
		{
			if (tmp.t > EPSILON && tmp.t < max_len)
				return (true);
		}
		else if (obj->type == OBJ_PL && hit_plane(ray,
				(t_plane *)obj->data, &tmp))
		{
			if (tmp.t > EPSILON && tmp.t < max_len)
				return (true);
		}
		else if (obj->type == OBJ_CY && hit_cylinder(ray,
				(t_cylinder *)obj->data, &tmp))
		{
			if (tmp.t > EPSILON && tmp.t < max_len)
				return (true);
		}
		obj = obj->next;
	}
	return (false);
}

/**
 * @brief 	check if a point is in shadow relative to a light source
 *
 * @param 	rec hit record at the point being checked
 * @param 	light light source
 * @param 	*obj object list in the scene
 * @return 	void
 * @note 	To determine if a point is in shadow relative to a light source,
			we cast a "shadow ray" from the point towards the light source.
			If this shadow ray intersects any object before reaching the light,
			the point is considered to be in shadow.
			We offset the shadow ray's origin slightly along the surface normal
			to avoid self-shadowing artifacts (commonly known as "shadow acne").
			EPSILON is a small constant used for this offset.
 */
bool	is_in_shadow(t_hit_record rec, t_light light, t_object *obj)
{
	t_ray	shadow;
	float	light_len;

	shadow.origin = vec_add(rec.point,
			vec_scale(rec.normal, EPSILON));
	shadow.direction = vec_normalize(vec_sub(light.l_point,
				rec.point));
	light_len = vec_len(vec_sub(light.l_point, rec.point));
	return (hit_shadow(shadow, obj, light_len));
}
