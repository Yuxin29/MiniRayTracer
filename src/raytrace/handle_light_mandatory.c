#include "miniRT.h"

/**
 * @brief 	calculate the final color at the hit point considering ambient and diffuse lighting
 *
 * @param 	*scene scene containing camera and lighting info
 * @param 	rec hit record at the point being lit
 * @return 	t_color final color at the hit point
 *
 * @note	final_color = ambient + diffuse
 */
t_color	final_color(t_scene *scene, t_hit_record rec)
{
	t_color	final;
	t_color	ambient;
	t_color	diffuse;
	t_color	obj_color;

	obj_color = get_color_from_object(rec.obj);
	ambient = apply_ambient(obj_color, scene->ambient_light);
	if (is_in_shadow(rec, scene->light, scene->objects))
		diffuse = (t_color){0, 0, 0};
	else
		diffuse = apply_diffuse(obj_color, scene->light, rec);
	final.r = clamp(ambient.r + diffuse.r, 0, 255);
	final.g = clamp(ambient.g + diffuse.g, 0, 255);
	final.b = clamp(ambient.b + diffuse.b, 0, 255);
	return (final);
}
