#include "miniRT.h"

/*
should control the value from 0-255
*/
int	clamp(int value, int min, int max)
{
	if (value > max)
		return (max);
	if (value < min)
		return (min);
	return (value);
}

/*
uint8_t * float => float, but unit8_t is int;
so i should cast the value to int before do clamp
ambient_color = object_color * ambient_light_color * ambient_ratio;
*/
t_color	apply_ambient(t_color obj_color, t_a_light amb)
{
	t_color	result;

	result.r = clamp((int)obj_color.r * (amb.rgb.r / 255.0f)
			* amb.ratio, 0, 255);
	result.g = clamp((int)obj_color.g * (amb.rgb.g / 255.0f)
			* amb.ratio, 0, 255);
	result.b = clamp((int)obj_color.b * (amb.rgb.b / 255.0f)
			* amb.ratio, 0, 255);
	return (result);
}

/*
color = ambient_color * ambient_ratio
diffuse_strength = max(dot(N, L), 0.0)
final_color = ambient + (obj_color.r
* light_color.r/255 * brightness * diffuse_strength);
N = surface normal at the hit point
L = direction to the light
*/
t_color	apply_diffuse(t_color obj_color, t_light light, t_hit_record rec)
{
	float	diffuse_strength;
	t_vec3	light_dir;
	t_color	color;

	light_dir = vec_normalize(vec_sub(light.l_point, rec.point));
	diffuse_strength = vec_dot(rec.normal, light_dir);
	if (diffuse_strength < 0.0f)
		diffuse_strength = 0.0f;
	color.r = clamp((int)obj_color.r * (light.rgb.r / 255.0f)
			* light.br_ratio * diffuse_strength, 0, 255);
	color.g = clamp((int)obj_color.g * (light.rgb.g / 255.0f)
			* light.br_ratio * diffuse_strength, 0, 255);
	color.b = clamp((int)obj_color.b * (light.rgb.b / 255.0f)
			* light.br_ratio * diffuse_strength, 0, 255);
	return (color);
}

t_color	get_color_from_object(t_object *obj)
{
	if (obj->type == OBJ_SP)
		return (((t_sphere *)obj->data)->rgb);
	else if (obj->type == OBJ_PL)
		return (((t_plane *)obj->data)->rgb);
	else if (obj->type == OBJ_CY)
		return (((t_cylinder *)obj->data)->rgb);
	return ((t_color){0, 0, 0});
}
