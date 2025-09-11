#include "miniRT.h"
#include "parsing.h"

static void	err_return(char *str)
{
	if (str)
		ft_putstr_fd(str, 1);
	return ;
}

void get_sphere(char *line, t_scene *scene)
{
	t_sphere	*new_sp;
	t_sphere	*tmp;
	char		**phases;
	char		**vec_1;
	char		**vec_2;

	new_sp = malloc(sizeof(t_sphere));
	if (!new_sp)
		return (err_return("malloc failure inside t_scene\n"));
	ft_bzero(new_sp, sizeof(t_sphere));;
	phases = ft_split(line, ' ');
	if (!phases)
		return (err_return("malloc failure inside t_scene\n"));
	vec_1 = ft_split(phases[1], ',');
	vec_2 = ft_split(phases[3], ',');
	if (!vec_1 || !vec_2)
		return (err_return("malloc failure inside t_scene\n"));
	ft_filling_vec(vec_1, &new_sp->sp_center);
	new_sp->dia = ft_atoi_float(phases[2]);
	new_sp->r = ft_atoi((const char *)vec_2[0]);
	new_sp->g = ft_atoi((const char *)vec_2[1]);
	new_sp->b = ft_atoi((const char *)vec_2[2]);
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
}

// void get_plane(char *line, t_scene *scene)
// {

// }

// void get_cylinder(char *line, t_scene *scene)
// {

// }