#include "miniRT.h"

//Mathematically: P(t)=origin+t⋅direction
//why? :  we need to find “where” a ray hits something, this function calculates that point.
//A ray is a half-infinite line in 3D space, starting from a point and going in a direction.
t_vec3	ray_at(t_ray a, float t)
{
	return (vec_add(a.origin, vec_scale(a.direction, t)));
}

static bool	update_hit_record(t_hit_record *tmp, float *closest_t, t_hit_record *rec, t_object *obj)
{
	bool	any_hit;

	any_hit = false;
	if(tmp->t < *closest_t)
	{
		*closest_t = tmp->t;
		*rec = *tmp;
		if (obj->type == OBJ_SP)
			rec->rgb = ((t_sphere *)obj->data)->rgb;
		else if(obj->type == OBJ_PL)
			rec->rgb = ((t_plane *)obj->data)->rgb;
		else if(obj->type == OBJ_CY)
			rec->rgb = ((t_cylinder *)obj->data)->rgb;
		any_hit = true;
	}
	return (any_hit);
}

bool	hit_objects(t_ray ray, t_object *obj, t_hit_record *rec)
{
	bool			cur_hit;
	t_hit_record	tmp;
	float			closest_t;
	bool			any_hit;

	closest_t = INFINITY;
	any_hit = false;
	while(obj)
	{

		cur_hit = false;
		if (obj->type == OBJ_SP)
			cur_hit = hit_sphere(ray, (t_sphere *)obj->data, &tmp);
		// else if(obj->type == OBJ_PL)
		// 	cur_hit = hit_plane(ray, (t_plane *)obj->data, &tmp);
		// else if(obj->type == OBJ_CY)
		// 	cur_hit = hit_cylinder(ray, (t_cylinder *)obj->data, &tmp);
		if (cur_hit)
			any_hit = update_hit_record(&tmp, &closest_t, rec, obj);
		obj = obj->next;
	}
	return (any_hit);
}
