#include "miniRT.h"
#include "render.h"
#include "parsing.h"

//from the subject
//  Your program must be able to apply translation 
// and rotation transformation to objects, lights and cameras 
// (except for spheres and lights that cannot be rotated
void	change_move(t_scene *scene, t_vec3 move)
{
	t_object	*cur;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	cur = scene->objects;
	while (cur)
	{
		if (cur->type == OBJ_SP)
		{
			sp = (t_sphere *)cur->data;
			sp->sp_center = vec_add(sp->sp_center, move);
		}
		if (cur->type == OBJ_PL)
		{
			pl = (t_plane *)cur->data;
			pl->p_in_pl = vec_add(pl->p_in_pl, move);
		}
		if (cur->type == OBJ_CY)
		{
			cy = (t_cylinder *)cur->data;
			cy->cy_center = vec_add(cy->cy_center, move);
		}
		cur = cur->next;
	}
}

//from the subject
// Your program must be able to resize the object’s unique properties: 
// diameter for a sphere and the width and height for a cylinder
void	change_zoomin(t_scene *scene, float scale)
{
	t_object	*cur;
	t_sphere	*sp;
	t_cylinder	*cy;

	cur = scene->objects;
	while (cur)
	{
		if (cur->type == OBJ_SP)
		{
			if (scale != 0)
			{
				sp = (t_sphere *)cur->data;
				sp->radius = sp->radius * scale;
			}
		}
		if (cur->type == OBJ_CY)
		{
			cy = (t_cylinder *)cur->data;
			cy->radius = cy->radius * scale;
			cy->height = cy->height * scale;
		}
		cur = cur->next;
	}
}

// vrot​=v⋅cosθ+(k×v)⋅sinθ+k⋅(k⋅v)(1−cosθ)
// float	vec_dot(t_vec3 a, t_vec3 b)
// t_vec3	vec_cross(t_vec3 a, t_vec3 b)//only modify the length
// t_vec3	vec_scale(t_vec3 a, float scalar)
// k = vec_normalize(k); 
// // I Dont really need this, because I always put int {0, 1, 0}
static t_vec3	vec_rotate(t_vec3 v, t_vec3 k, float angle)
{
	t_vec3	v_1;
	t_vec3	v_2;
	t_vec3	v_3;

	k = vec_normalize(k);
	v_1 = vec_scale(v, cos(angle));
	v_2 = vec_scale(vec_cross(k, v), sin(angle));
	v_3 = vec_scale(k, vec_dot(k, v) * (1 - cos(angle)));
	return (vec_add(v_1, vec_add(v_2, v_3)));
}
//Your program must be able to apply translation and rotation transformation 
// toobjects, lights and cameras 
// (except for spheres and lights that cannot be rotated).
void	change_rotation(t_scene *scene, t_vec3 y_axis, float angle)
{
	t_object	*cur;
	t_plane		*pl;
	t_cylinder	*cy;

	cur = scene->objects;
	while (cur)
	{
		if (cur->type == OBJ_PL)
		{
			pl = (t_plane *)cur->data;
			pl->nor_v = vec_rotate(pl->nor_v, y_axis, angle);
		}
		if (cur->type == OBJ_CY)
		{
			cy = (t_cylinder *)cur->data;
			cy->cy_axis = vec_rotate(cy->cy_axis, y_axis, angle);
		}
		cur = cur->next;
	}
	scene->cam.v_orien = vec_rotate(scene->cam.v_orien, y_axis, angle);
}
