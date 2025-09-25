#include "miniRT.h"

//helper functions for the validate_parsing_tokens_sp below
static bool	fill_sp_bi_info(char **tokens, t_sphere *new_sp)
{
	char	**vec_1;
	char	**colors;

	vec_1 = ft_split(tokens[1], ',');
	colors = ft_split(tokens[3], ',');
	if (!do_color(colors, &(new_sp->rgb))
		|| !do_xyz_vectoy(vec_1, &new_sp->sp_center))
	{
		free_three_arr(vec_1, colors, NULL);
		return (false);
	}
	free_three_arr(vec_1, colors, NULL);
	return (true);
}

static bool	fill_sp_float(char **tokens, t_sphere *new_sp)
{
	if (!check_valid_float(tokens[2]))
		return (false);
	new_sp->radius = ft_atoi_float(tokens[2]) / 2;
	if (new_sp->radius <= 0 || new_sp->radius > 1000)
		return (false);
	return (true);
}

// Sphere:
// sp 0.0,0.0,20.6 12.6 10,0,255
// ∗ identifier: sp
// ∗ x,y,z coordinates of the sphere center: 0.0,0.0,20.6
// ∗ the sphere diameter: 12.6
// ∗ R,G,B colors in range [0-255]: 10, 0, 255
// the sphere diameter: can not be minus, can not be too big
bool	validate_parsing_tokens_sp(char **tokens, t_scene *scene)
{
	t_sphere	*new_sp;

	if (count_token_nbr(tokens) != 4)
		return (false);
	new_sp = ft_calloc(1, sizeof(t_sphere));
	if (!new_sp)
		return (false);
	if (!fill_sp_float(tokens, new_sp))
	{
		free (new_sp);
		return (false);
	}
	if (!fill_sp_bi_info(tokens, new_sp))
	{
		free (new_sp);
		return (false);
	}
	if (!add_obj_to_scene(scene, OBJ_SP, new_sp))
	{
		free(new_sp);
		return (false);
	}
	return (true);
}
