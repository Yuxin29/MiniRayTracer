#include "miniRT.h"
#include "parsing.h"

bool	validate_parsing_tokens_sp(char **tokens, t_scene *scene)
{
	t_sphere	*new_sp;
	t_sphere	*tmp;
	char		**vec_1;
	char		**colors;

	new_sp = malloc(sizeof(t_sphere));
	if (!new_sp)
		return (false);
	ft_bzero(new_sp, sizeof(t_sphere));
	new_sp->dia = ft_atoi_float(tokens[2]);
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

bool	validate_parsing_tokens_pl(char **tokens, t_scene *scene)
{
	t_plane	*new_pl;
	t_plane	*tmp;
	char	**vec_1;
	char	**vec_2;
	char	**colors;

	new_pl = malloc(sizeof(t_plane));
	if (!new_pl)
		return (false);
	ft_bzero(new_pl, sizeof(t_plane));
	vec_1 = ft_split(tokens[1], ',');
	vec_2 = ft_split(tokens[2], ',');
	colors = ft_split(tokens[3], ',');
	if (!do_normalized_vectoy(vec_2, &new_pl->nor_v)
		|| !do_xyz_vectoy(vec_1, &new_pl->p_in_pl)
		|| !do_color(colors, &(new_pl->rgb)))
	{
		free_three_arr(vec_1, vec_2, colors);
		free(new_pl);
		return (false);
	}
	free_three_arr(vec_1, vec_2, colors);
	new_pl->next = NULL;
	if (!scene->pl)
		scene->pl = new_pl;
	else
	{
		tmp = scene->pl;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_pl;
	}
	return (true);
}

bool	validate_parsing_tokens_cy(char **tokens, t_scene *scene)
{
	t_cylinder	*new_cy;
	t_cylinder	*tmp;
	char		**vec_1;
	char		**vec_2;
	char		**colors;

	new_cy = malloc(sizeof(t_cylinder));
	if (!new_cy)
		return (false);
	ft_bzero(new_cy, sizeof(t_cylinder));
	new_cy->dia = ft_atoi_float(tokens[3]);
	new_cy->height = ft_atoi_float(tokens[4]);
	new_cy->radius = new_cy->dia / 2;
	vec_1 = ft_split(tokens[1], ',');
	vec_2 = ft_split(tokens[2], ',');
	colors = ft_split(tokens[5], ',');
	if (!(do_normalized_vectoy(vec_2, &new_cy->cy_axis))
		|| !(do_xyz_vectoy(vec_1, &new_cy->cy_center))
		|| !do_color(colors, &(new_cy->rgb)))
	{
		free_three_arr(vec_1, vec_2, colors);
		free(new_cy);
		return (false);
	}
	free_three_arr(vec_1, vec_2, colors);
	new_cy->next = NULL;
	if (!scene->cl)
		scene->cl = new_cy;
	else
	{
		tmp = scene->cl;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cy;
	}
	return (true);
}
