#include "miniRT.h"

/**
 * @brief 	the ray-cylinder intersection function called in rendering scene
 *
 * @param 	ray ray to be checked for intersection
 * @param 	*cylinder cylinder to be checked for intersection
 * @param 	*rec hit record to store intersection info	
 * @return 	bool indicating if there was a hit
 *
 */
bool	hit_cylinder(t_ray ray, t_cylinder *cy, t_hit_record *rec)
{
	t_hit_record	body_hit;
	t_hit_record	cap_hit;
	bool			body;
	bool			caps;

	body = hit_cylinder_body(ray, cy, &body_hit);
	caps = hit_cylinder_caps(ray, cy, &cap_hit);
	if (body && (!caps || body_hit.t < cap_hit.t))
	{
		*rec = body_hit;
		return (true);
	}
	else if (caps)
	{
		*rec = cap_hit;
		return (true);
	}
	return (false);
}
