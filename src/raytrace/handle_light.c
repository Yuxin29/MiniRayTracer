#include "miniRT.h"

/*
should control the value from 0-255
*/
static int	clamp(int value, int min, int max)
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
static t_color apply_ambient(t_color obj_color, t_a_light amb)
{
	t_color result;

	result.r = clamp((int)obj_color.r * (amb.rgb.r / 255.0f) * amb.ratio, 0, 255);
	result.g = clamp((int)obj_color.g * (amb.rgb.g / 255.0f) * amb.ratio, 0, 255);
	result.b = clamp((int)obj_color.b * (amb.rgb.b / 255.0f) * amb.ratio, 0, 255);
	return (result);
}

/*
color = ambient_color * ambient_ratio
diffuse_strength = max(dot(N, L), 0.0)
final_color = ambient + (obj_color.r * light_color.r/255 * brightness * diffuse_strength);
N = surface normal at the hit point
L = direction to the light
*/
static t_color	apply_diffuse(t_light light, t_hit_record rec)
{
	float	diffuse_strength;
	t_vec3	light_dir;
	t_color	color;

	light_dir = vec_normalize(vec_sub(light.l_point, rec.point));
	diffuse_strength = vec_dot(rec.normal, light_dir);
	if (diffuse_strength < 0.0f)
		diffuse_strength = 0.0f;
	color.r = clamp((int)rec.rgb.r * (light.rgb.r / 255.0f) * light.br_ratio * diffuse_strength, 0, 255);
	color.g = clamp((int)rec.rgb.g * (light.rgb.g / 255.0f) * light.br_ratio * diffuse_strength, 0, 255);
	color.b = clamp((int)rec.rgb.b * (light.rgb.b / 255.0f) * light.br_ratio * diffuse_strength, 0, 255);
	return (color);
}

/*
final_color = ambient + diffuse
*/
t_color	final_color(t_color obj_color, t_a_light amb, t_light light, t_hit_record rec)
{
	t_color	final;
	t_color	ambient;
	t_color	diffuse;

	ambient = apply_ambient(obj_color, amb);
	diffuse = apply_diffuse(light, rec);
	final.r = clamp(ambient.r + diffuse.r, 0, 255);
	final.g = clamp(ambient.g + diffuse.g, 0, 255);
	final.b = clamp(ambient.b + diffuse.b, 0, 255);
	return (final);
}
