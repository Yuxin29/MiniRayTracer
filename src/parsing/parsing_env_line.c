#include "miniRT.h"
#include "parsing.h"

bool	validate_parsing_tokens_a(char **tokens, t_scene *scene)
{
	char	**colors;

	ft_bzero(&scene->ambient_light, sizeof(t_a_light));
	if (check_valid_float(tokens[1]))
		scene->ambient_light.ratio = ft_atoi_float(tokens[1]);
	else
		return (false);
	colors = ft_split(tokens[2], ',');
	if (!do_color(colors, &(scene->ambient_light.rgb)))
	{
		if (colors)
			ft_free_arr(colors);
		return (false);
	}
	ft_free_arr(colors);
	return (true);
}

bool	validate_parsing_tokens_c(char **tokens, t_scene *scene)
{
	char	**vec_1;
	char	**vec_2;

	ft_bzero(&scene->cam, sizeof(t_camera));
	if (check_valid_float(tokens[3]))
		scene->cam.fov = ft_atoi_float(tokens[3]);
	else
		return (false);
	vec_1 = ft_split(tokens[1], ',');
	vec_2 = ft_split(tokens[2], ',');
	if (!do_xyz_vectoy(vec_1, &scene->cam.v_point)
		|| !do_normalized_vectoy(vec_2, &scene->cam.v_orien))
	{
		free_three_arr(vec_1, vec_2, NULL);
		return (false);
	}
	free_three_arr(vec_1, vec_2, NULL);
	return (true);
}

bool	validate_parsing_tokens_l(char **tokens, t_scene *scene)
{
	char	**vec;

	ft_bzero(&scene->light, sizeof(t_light));
	if (check_valid_float(tokens[2]))
		scene->light.br_ratio = ft_atoi_float(tokens[2]);
	else
		return (false);
	vec = ft_split(tokens[1], ',');
	if (!do_xyz_vectoy(vec, &scene->light.l_point))
	{
		if (vec)
			ft_free_arr(vec);
		return (false);
	}
	ft_free_arr(vec);
	return (true);
}

static bool	fill_sp_bio_data(char **tokens, t_sphere	*new_sp)
{
	char	**vec_1;
	char	**colors;

	vec_1 = ft_split(tokens[1], ',');
	colors = ft_split(tokens[3], ',');
	if (!do_color(colors, &(new_sp->rgb))
		|| !do_xyz_vectoy(vec_1, &new_sp->sp_center))
	{
		free_three_arr(vec_1, NULL, colors);
		free(new_sp);
		return (false);
	}
	free_three_arr(vec_1, NULL, colors);
	return (true);
}

bool	validate_parsing_tokens_sp(char **tokens, t_scene *scene)
{
	t_sphere	*new_sp;
	t_sphere	*tmp;

	new_sp = malloc(sizeof(t_sphere));
	if (!new_sp)
		return (false);
	ft_bzero(new_sp, sizeof(t_sphere));
	if (check_valid_float(tokens[2]))
		new_sp->dia = ft_atoi_float(tokens[2]);
	else
		return (false);
	if (!fill_sp_bio_data(tokens, new_sp))
		return (false);
	new_sp->next = NULL;
	if (!scene->sp)
		scene->sp = new_sp;
	else
	{
		tmp = scene->sp;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_sp;
	}
	return (true);
}
