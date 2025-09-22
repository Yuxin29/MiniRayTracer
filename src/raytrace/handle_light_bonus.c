#include "miniRT_bonus.h"  


// if
//Ispec ​= k ​⋅ Ilight ​⋅ (max(R⋅V ,0)) shininess
// k: specular strenghth (0 - 1.0)
// I: light brightness
// R: vector: reflective vec
// V: vector: ray vec
// shininess: exponent (controls "sharpness" of highlight, e.g. 16, 32, 64)
// static t_color apply_specular(t_light light, t_hit_record rec, cam_pos pos)
// {

// }

// typedef struct s_hit_record
// {
// 	float	t; //t represents how far along the ray we go to reach the hit point.
// 	t_vec3	point; //hit point
// 	t_vec3	normal; //A normal is a vector that points perpendicular to the surface at a specific point.
// 	t_color	rgb; //0916modify
// }	t_hit_record;
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
static	t_color apply_checkerboard(t_hit_record rec, t_color original_color)
{
	int x;
	int z; 

	x = floorf(rec.point.x);
    z = floorf(rec.point.z);
	if (((abs(x + z)) % 2) == 0) //double not change
		return (original_color);
	else //single reverse
		return (t_color){255 - original_color.r, 255 - original_color.g, 255 - original_color.b}; 
}

//this one from lin, just need to apply checkerboard color here
/*
final_color = ambient + diffuse
*/
/*
final_color = ambient + diffuse
*/
t_color	final_color(t_scene *scene, t_hit_record rec)
{
	t_color	final;
	t_color	ambient;
	t_color	diffuse;
	t_color	obj_color;
	//t_color	specular;

	obj_color = get_color_from_object(rec.obj);
	obj_color = apply_checkerboard(rec, obj_color);  //this line added
	ambient = apply_ambient(obj_color, scene->ambient_light);
	if(is_in_shadow(rec, scene->light, scene->objects))
	{
		diffuse = (t_color){0, 0, 0};
		//specular = (t_color){0, 0, 0};
	}
	else
	{
		diffuse = apply_diffuse(obj_color, scene->light, rec);
		//specular = apply_specular(scene->light, rec, scene->cam.cam_pos);
	}
	final.r = clamp(ambient.r + diffuse.r, 0, 255);
	final.g = clamp(ambient.g + diffuse.g, 0, 255);
	final.b = clamp(ambient.b + diffuse.b, 0, 255);
	// final.r = clamp(ambient.r + diffuse.r + specular.r, 0, 255);
	// final.g = clamp(ambient.g + diffuse.g + specular.g, 0, 255);
	// final.b = clamp(ambient.b + diffuse.b + specular.b, 0, 255);
	return (final);
}