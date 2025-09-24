#include "miniRT_bonus.h"

// reflective vec formular
// R = 2(N·L)N - L
static float	get_max(t_light light, t_hit_record rec, t_vec3 pos)
{
	t_vec3	reflective_vec;
	t_vec3	view_vec;
	t_vec3	light_vec;
	float	two_nl;
	float	rv;

	light_vec = vec_normalize(vec_sub(light.l_point, rec.point));
	two_nl = 2.0f * vec_dot(rec.normal, light_vec);
	reflective_vec = vec_sub(vec_scale(rec.normal, two_nl), light_vec);
	view_vec = vec_normalize(vec_sub(pos, rec.point));
	rv = vec_dot(reflective_vec, view_vec);
	if (rv < 0.0)
		rv = 0.0;
	return (rv);
}

//Ispec ​= k ​⋅ Ilight ​⋅ (max(R⋅V ,0)) shininess
// k: specular strenghth (0 - 1.0)
// I: light brightness
// R: vector: reflective vec
// V: vector: ray vec
// shininess: exponent (controls "sharpness" of highlight, e.g. 16, 32, 64)
// Ispec = k * light * br * powerpart
// res_color.r = clamp(light.rgb.r * light.br_ratio * k * power_part, 0, 255); 	
static t_color	apply_specular(t_light light, t_hit_record rec, t_vec3 pos)
{
	int		shininess;
	float	rv;
	float	power;
	float	k;
	t_color	res_color;

	k = SPEC_K;
	shininess = SPEC_SHININESS;
	rv = get_max(light, rec, pos);
	power = powf(rv, shininess);
	res_color.r = clamp(light.rgb.r * light.br_ratio * k * power, 0, 255);
	res_color.g = clamp(light.rgb.g * light.br_ratio * k * power, 0, 255);
	res_color.b = clamp(light.rgb.b * light.br_ratio * k * power, 0, 255);
	return (res_color);
}

//yuxin added for checkerboard
//after hit obj, use (x, z) to decide is it single or double
// #include <stdlib.h>
// int abs(int x); absolute value
// floorf rounded a float down to an int
// why floorf
// intput x		(int)x				floorf(x)
// -1.9			-1					-2
// -1.2			-1					-2
// -0.7			0					-1
// 	0.7			0					0
// 	1.2			1					1
//				rounded towards 0	always round down
//double not change, //single reverse
// to be FIX on tuesday, it should be u, v instead of directly x and z
static t_color	apply_checkerboard(t_hit_record rec, t_color original_color)
{
	t_vec3	u_axis;
	t_vec3	v_axis;
	t_vec3	rel;
	int		u;
	int		v;

	if (rec.normal.y > 0.99 || rec.normal.y < -0.99)
		u_axis = vec_cross((t_vec3){1, 0, 0}, rec.normal);
	else
		u_axis = vec_cross((t_vec3){0, 1, 0}, rec.normal);
	u_axis = vec_normalize(u_axis);
	v_axis = vec_normalize(vec_cross(rec.normal, u_axis));
	rel = vec_sub(rec.point, ((t_plane *)rec.obj->data)->p_in_pl);
	u = (int)floorf(vec_dot(rel, u_axis));
	v = (int)floorf(vec_dot(rel, v_axis));
	if ((u + v) % 2 != 0)
	{
		original_color.r = 255 - original_color.r;
		original_color.g = 255 - original_color.g;
		original_color.b = 255 - original_color.b;
	}
	return (original_color);
}

//this one from lin, just need to apply checkerboard color here
// final_color = ambient + diffuse (+ specular)
// t_color final_color(t_scene *scene, t_hit_record rec, t_object *obj)
t_color	final_color(t_scene *scene, t_hit_record rec)
{
	t_color	final;
	t_color	ambient;
	t_color	diffuse;
	t_color	obj_color;
	t_color	specular;

	obj_color = get_color_from_object(rec.obj);
	if (rec.obj->type == OBJ_PL && USE_CHECKERBOARD)
		obj_color = apply_checkerboard(rec, obj_color);
	ambient = apply_ambient(obj_color, scene->ambient_light);
	specular = (t_color){0, 0, 0};
	diffuse = (t_color){0, 0, 0};
	if (!is_in_shadow(rec, scene->light, scene->objects))
	{
		diffuse = apply_diffuse(obj_color, scene->light, rec);
		specular = apply_specular(scene->light, rec, scene->cam.v_point);
	}
	final.r = clamp(ambient.r + diffuse.r + specular.r, 0, 255);
	final.g = clamp(ambient.g + diffuse.g + specular.g, 0, 255);
	final.b = clamp(ambient.b + diffuse.b + specular.b, 0, 255);
	return (final);
}
