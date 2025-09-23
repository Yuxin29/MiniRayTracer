#include "miniRT.h"
#include "raytrace.h"

bool	hit_bottom_cap(t_ray ray, t_cylinder *cy, t_hit_record *rec)
{
	t_vec3			bottom_cen;
	t_plane			bot_plane;
	t_hit_record	tmp_rec;
	float			bot_len;

	bottom_cen = vec_sub(cy->cy_center,
			vec_scale(cy->cy_axis, cy->height / 2.0f));
	bot_plane.p_in_pl = bottom_cen;
	bot_plane.nor_v = vec_scale(cy->cy_axis, -1);
	if (hit_plane(ray, &bot_plane, &tmp_rec))
	{
		bot_len = vec_len(vec_sub(tmp_rec.point, bottom_cen));
		if (bot_len <= cy->radius)
		{
			*rec = tmp_rec;
			return (true);
		}
	}
	return (false);
}

/*
A cylinder is not infinitely long — it has a top cap and a bottom cap,
and the valid hit region is between them.
top_center = cy_center + (axis * (height / 2))
bottom_center = cy_center - (axis * (height / 2))
*/
bool	hit_top_cap(t_ray ray, t_cylinder *cy, t_hit_record *rec)
{
	t_vec3			top_cen;
	t_plane			top_plane;
	t_hit_record	tmp_rec;
	float			top_len;

	top_cen = vec_add(cy->cy_center,
			vec_scale(cy->cy_axis, cy->height / 2.0f));
	top_plane.p_in_pl = top_cen;
	top_plane.nor_v = cy->cy_axis;
	if (hit_plane(ray, &top_plane, &tmp_rec))
	{
		top_len = vec_len(vec_sub(tmp_rec.point, top_cen));
		if (top_len <= cy->radius)
		{
			*rec = tmp_rec;
			return (true);
		}
	}
	return (false);
}
