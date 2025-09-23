#include "miniRT_bonus.h"

// reflective vec formular
// R = 2(N·L)N - L
static float	get_max(t_light light, t_hit_record rec, t_vec3 pos)
{
	t_vec3	reflective_vec;
	t_vec3	view_vec;
	t_vec3	light_vec;
	float	rv;

	light_vec = vec_normalize(vec_sub(light.l_point, rec.point));
	view_vec = vec_normalize(vec_sub(pos, rec.point));
	reflective_vec = vec_sub(vec_scale(rec.normal, 2.0f * vec_dot(rec.normal, light_vec)), light_vec);
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
//  res_color.r = clamp(light.rgb.r * light.br_ratio * k * power_part, 0, 255); 	
static t_color	apply_specular(t_light light, t_hit_record rec, t_vec3 pos)
{
	int		shininess;
	float	rv;
	float	power;
	t_color	res_color;
	float	k;

	k = 0.5;
	shininess = 16;
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
	int	x;
	int	z; 

	x = floorf(rec.point.x);
	z = floorf(rec.point.z);
	if (((abs(x + z)) % 2) == 0)
		return (original_color);
	else
		return (t_color){255 - original_color.r, 255 - original_color.g, 255 - original_color.b}; 
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
	if (rec.obj->type == OBJ_PL)
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
