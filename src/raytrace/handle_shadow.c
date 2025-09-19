#include "miniRT.h"

/*
Ray equation:P(t) = O + tD
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
	float			t;

	t = INFINITY;
	while (obj)
	{
		if (obj->type == OBJ_SP && hit_sphere(ray, (t_sphere *)obj->data, &tmp))
			t = tmp.t;
		else if (obj->type == OBJ_PL && hit_plane(ray, (t_plane *)obj->data, &tmp))
			t = tmp.t;
		// else if (obj->type == OBJ_CY && hit_cylinder(ray, (t_cylinder *)obj->data, &tmp))
			// 	t = tmp.t;
		if (t > EPSILON && t < max_len)
			return (true);
		obj = obj->next;
	}
	return (false);
}

bool	is_in_shadow(t_hit_record rec, t_light light, t_object *obj)
{
	t_ray	shadow;
	float	light_len;

	shadow.origin = vec_add(rec.point, vec_scale(rec.normal, EPSILON));
	shadow.direction = vec_normalize(vec_sub(light.l_point, rec.point));
	light_len = vec_len(vec_sub(light.l_point, rec.point));
	return(hit_shadow(shadow, obj, light_len));
}
