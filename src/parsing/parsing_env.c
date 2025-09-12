#include "miniRT.h"
#include "parsing.h"

bool validate_parsing_tokens_a(char **tokens, t_scene *scene)
{
	char	**colors;

	if (count_token_nbr(tokens) != 3)
		return false;
	scene->ambient_light = malloc(sizeof(t_a_light));
	if (!scene->ambient_light)
		return false;
	ft_bzero(scene->ambient_light, sizeof(t_a_light));
	colors = ft_split(tokens[2], ',');
	if (!colors)
		return false; //need to have error msgs??
	printf("%s\n", "debug2");
	printf("%d\n", check_rgb(colors));
	if (!check_rgb(colors))
	{
		ft_free_arr(colors);
		return false;
	}
	printf("%s\n", "debug2");
	do_color(colors, &(scene->ambient_light->rgb));
	//float not check yet
	scene->ambient_light->ratio = ft_atoi_float(tokens[1]);
	ft_free_arr(colors);
	return true;
}

bool validate_parsing_tokens_c(char **tokens, t_scene *scene)
{
	char	**vec_1;
	char	**vec_2;

	if (count_token_nbr(tokens) != 4)
		return false;
	scene->cam = malloc(sizeof(t_camera));
	if (!scene->cam)
		return false;
	ft_bzero(scene->cam, sizeof(t_camera));
	vec_1 =  ft_split(tokens[1], ',');
	vec_2 =  ft_split(tokens[2], ',');
	scene->cam->fov = ft_atoi((const char *)tokens[3]);
	if (!vec_1 || !vec_2)
	{
		if (vec_1)
			ft_free_arr(vec_1);
		if (vec_2)
			ft_free_arr(vec_2);
		return false;
	}
	if (count_token_nbr(vec_1) != 3 || count_token_nbr(vec_2) != 3)
	{
		ft_free_arr(vec_1);
		ft_free_arr(vec_2);
		return false;
	}
	ft_filling_vec(vec_1, &scene->cam->v_point);//not check vec values yet
	ft_filling_vec(vec_2, &scene->cam->v_orien);//not check vec values yet
	ft_free_arr(vec_1);
	ft_free_arr(vec_2);
	return true;
}

// static void get_light(char *line, t_scene *scene)
// {

// }

