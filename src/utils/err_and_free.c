#include "utils.h"
#include "miniRT.h"
#include "parsing.h"



//free linked list objects
static void	ft_free_linked_objects(t_scene *scene)
{
	t_sphere	*sp_tmp;
	t_plane		*pl_tmp;
	t_cylinder	*cl_tmp;

	while (scene->sp)
	{
		sp_tmp = scene->sp->next;
		free(scene->sp);
		scene->sp = sp_tmp;
	}
	scene->sp = NULL;
	while (scene->pl)
	{
		pl_tmp = scene->pl->next;
		free(scene->sp);
		scene->pl = pl_tmp;
	}
	scene->pl = NULL;
	while (scene->cl)
	{
		cl_tmp = scene->cl->next;
		free(scene->cl);
		scene->cl = cl_tmp;
	}
	scene->cl = NULL;
}

void	ft_free_scene(t_scene *scene)
{
	ft_free_linked_objects(scene);
	if (scene->fd > -1)
		close(scene->fd);
	if (scene->img && scene->mlx)
		mlx_delete_image(scene->mlx, scene->img);
	if (scene->mlx)
		mlx_terminate(scene->mlx);
	free(scene);
}
