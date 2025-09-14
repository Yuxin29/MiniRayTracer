#include "miniRT.h"
#include "parsing.h"

bool	validate_parsing_tokens_a(char **tokens, t_scene *scene)
{
	char	**colors;

	ft_bzero(&scene->ambient_light, sizeof(t_a_light));
	scene->ambient_light.ratio = ft_atoi_float(tokens[1]); //float not check yet
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
	scene->cam.fov = ft_atoi((const char *)tokens[3]);
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
	scene->light.br_ratio = ft_atoi((const char *)tokens[2]);
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
