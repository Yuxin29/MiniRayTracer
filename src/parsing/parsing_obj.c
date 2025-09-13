#include "miniRT.h"
#include "parsing.h"

bool validate_parsing_tokens_sp(char **tokens, t_scene *scene)
{
	t_sphere	*new_sp;
	t_sphere	*tmp;
	char		**vec_1;
	char		**vec_2;

	new_sp = malloc(sizeof(t_sphere));
	if (!new_sp)
		return (false);
	ft_bzero(new_sp, sizeof(t_sphere));;
	vec_1 = ft_split(tokens[1], ',');
	vec_2 = ft_split(tokens[3], ',');
	new_sp->dia = ft_atoi_float(tokens[2]);
	if (!vec_1 || !vec_2)
	{
		if (vec_1)
			ft_free_arr(vec_1);
		if (vec_2)
			ft_free_arr(vec_2);
		free(new_sp);
		return (false);
	}
	if(count_token_nbr(vec_1) != 3)
	{
		ft_free_arr(vec_1);
		ft_free_arr(vec_2);
		free(new_sp);
		return (false);
	}
	ft_filling_vec(vec_1, &new_sp->sp_center); //not check vec_1yet
	if (!check_rgb(vec_2))
	{
		ft_free_arr(vec_1);
		ft_free_arr(vec_2);
		free(new_sp);
		return (false);
	}
	do_color(vec_2, &(new_sp->rgb));
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
	free(new_sp);
	ft_free_arr(vec_1);
	ft_free_arr(vec_2);
	return true;
}

// void get_plane(char *line, t_scene *scene)
// {

// }

// void get_cylinder(char *line, t_scene *scene)
// {

// }