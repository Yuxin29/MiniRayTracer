#include "miniRT.h"
#include "parsing.h"

// Ambient lightning:
// identifier: A
// ambient lighting ratio in range [0.0,1.0]: 0.2
// R,G,B colors in range [0-255]: 255, 255, 255
bool	validate_parsing_tokens_a(char **tokens, t_scene *scene)
{
	char	**colors;

	ft_bzero(&scene->ambient_light, sizeof(t_a_light));
	if (check_valid_float(tokens[1]))
		scene->ambient_light.ratio = ft_atoi_float(tokens[1]);
	else
		return (false);
	if (scene->ambient_light.ratio < 0 || scene->ambient_light.ratio > 1)
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

//identifier: C
// ∗ x,y,z coordinates of the view point: -50.0,0,20
// ∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
// 0.0,0.0,1.0
// ∗ FOV : Horizontal field of view in degrees in range [0,180]: 70
bool	validate_parsing_tokens_c(char **tokens, t_scene *scene)
{
	char	**vec_1;
	char	**vec_2;

	ft_bzero(&scene->cam, sizeof(t_camera));
	if (check_valid_float(tokens[3]))
		scene->cam.fov = ft_atoi_float(tokens[3]);
	else
		return (false);
	if (scene->cam.fov < 0 || scene->cam.fov > 180)
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

// Light:
// L -40.0,50.0,0.0 0.6 10,0,255
// ∗ identifier: L
// ∗ x,y,z coordinates of the light point: -40.0,50.0,0.0
// ∗ the light brightness ratio in range [0.0,1.0]: 0.6
// ∗ (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255
bool	validate_parsing_tokens_l(char **tokens, t_scene *scene)
{
	char	**vec;

	ft_bzero(&scene->light, sizeof(t_light));
	if (check_valid_float(tokens[2]))
		scene->light.br_ratio = ft_atoi_float(tokens[2]);
	else
		return (false);
	if (scene->light.br_ratio < 0 || scene->light.br_ratio > 1)
		return (false);
	vec = ft_split(tokens[1], ',');
	// if (!do_xyz_vectoy(vec, &scene->light.l_point))
	// {
	// 	if (vec)
	// 		ft_free_arr(vec);
	// 	return (false);
	// }
	scene->light.l_point.x = -ft_atoi_float(vec[0]); //should modify
	scene->light.l_point.y = ft_atoi_float(vec[1]);
	scene->light.l_point.z = ft_atoi_float(vec[2]);

	ft_free_arr(vec);
	scene->light.rgb.r = 255;
	scene->light.rgb.g = 255;
	scene->light.rgb.b = 255;
	return (true);
}
