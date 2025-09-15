#include "miniRT.h"
#include "parsing.h"

//helpers for validate_parsing_tokens_pl below
static bool	fill_pl_tria_data(char **tokens, t_plane *new_pl)
{
	char	**vec_1;
	char	**vec_2;
	char	**colors;

	vec_1 = ft_split(tokens[1], ',');
	vec_2 = ft_split(tokens[2], ',');
	colors = ft_split(tokens[3], ',');
	if (!do_normalized_vectoy(vec_2, &new_pl->nor_v)
		|| !do_xyz_vectoy(vec_1, &new_pl->p_in_pl)
		|| !do_color(colors, &(new_pl->rgb)))
	{
		free_three_arr(vec_1, vec_2, colors);
		return (false);
	}
	free_three_arr(vec_1, vec_2, colors);
	return (true);
}

// Plane:
// pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
// ∗ identifier: pl
// ∗ x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
// ∗ 3d normalized normal vector. 
// In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
// ∗ R,G,B colors in range [0-255]: 0,0,225
bool	validate_parsing_tokens_pl(char **tokens, t_scene *scene)
{
	t_plane	*new_pl;

	new_pl = malloc(sizeof(t_plane));
	if (!new_pl)
		return (false);
	ft_bzero(new_pl, sizeof(t_plane));
	if (!fill_pl_tria_data(tokens, new_pl))
	{
		free (new_pl);
		return (false);
	}
	if (!add_obj_to_scene(scene, OBJ_PL, new_pl))
	{
		free(new_pl);
		return (false);
	}
	return (true);
}

//helpers for fill_cy_float below
static bool	fill_cy_tria_data(char **tokens, t_cylinder	*new_cy)
{
	char	**vec_1;
	char	**vec_2;
	char	**colors;

	vec_1 = ft_split(tokens[1], ',');
	vec_2 = ft_split(tokens[2], ',');
	colors = ft_split(tokens[5], ',');
	if (!(do_normalized_vectoy(vec_2, &new_cy->cy_axis))
		|| !(do_xyz_vectoy(vec_1, &new_cy->cy_center))
		|| !do_color(colors, &(new_cy->rgb)))
	{
		free_three_arr(vec_1, vec_2, colors);
		return (false);
	}
	free_three_arr(vec_1, vec_2, colors);
	return (true);
}

//helpers for fill_cy_float below
// ∗ the cylinder diameter: can not be minus or too big
// ∗ the cylinder height: can not be minus or too big
static bool	fill_cy_float(char **tokens, t_cylinder	*new_cy)
{
	if (check_valid_float(tokens[3]) && check_valid_float(tokens[4]))
	{
		new_cy->radius = ft_atoi_float(tokens[3]) / 2;
		new_cy->height = ft_atoi_float(tokens[4]);
	}
	else
		return (false);
	if (new_cy->radius < 0 || new_cy->radius > 1000)
		return (false);
	if (new_cy->height < 0 || new_cy->height > 1000)
		return (false);
	return (true);
}

// Cylinder:
// cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
// ∗ identifier: cy
// ∗ x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
// ∗ 3d normalized vector of axis of cylinder. 
// In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
// ∗ the cylinder diameter: 14.2
// ∗ the cylinder height: 21.42
// ∗ R,G,B colors in range [0,255]: 10, 0, 255
bool	validate_parsing_tokens_cy(char **tokens, t_scene *scene)
{
	t_cylinder	*new_cy;

	new_cy = malloc(sizeof(t_cylinder));
	if (!new_cy)
		return (false);
	ft_bzero(new_cy, sizeof(t_cylinder));
	if (!fill_cy_float(tokens, new_cy))
	{
		free (new_cy);
		return (false);
	}
	if (!fill_cy_tria_data(tokens, new_cy))
	{
		free (new_cy);
		return (false);
	}
	if (!add_obj_to_scene(scene, OBJ_CY, new_cy))
	{
		free(new_cy);
		return (false);
	}
	return (true);
}
