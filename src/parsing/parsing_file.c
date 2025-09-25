#include "miniRT.h"

static void	delete_mlx(t_scene *scene)
{
	if (scene->mlx)
	{
		if (scene->img)
			mlx_delete_image(scene->mlx, scene->img);
		scene->img = NULL;
		mlx_terminate(scene->mlx);
		scene->mlx = NULL;
	}
	return ;
}

void	ft_free_scene(t_scene *scene)
{
	t_object	*obj_tmp;

	if (!scene)
		return ;
	if (scene->fd >= 0)
		close(scene->fd);
	scene->fd = -1;
	delete_mlx(scene);
	while (scene->objects)
	{
		obj_tmp = scene->objects->next;
		if (scene->objects->data)
		{
			free(scene->objects->data);
			scene->objects->data = NULL;
		}
		free(scene->objects);
		scene->objects = obj_tmp;
	}
	scene->objects = NULL;
	free(scene);
	scene = NULL;
}

//sub
// Your program must take as a first argument
// a scene description file with the .rt extension.
//check if file suffix valid // open file successful
static bool	check_file(char **av, t_scene *scene)
{
	char	*ext;

	ext = ft_strrchr(av[1], '.');
	if (!ext || ft_strcmp(ext, ".rt") != 0)
	{
		ft_putstr_fd("Error: wrong format\n", 2);
		return (false);
	}
	scene->fd = open(av[1], O_RDONLY);
	if (scene->fd == -1)
	{
		ft_putstr_fd("Error: open file failed\n", 2);
		return (false);
	}
	return (true);
}

//check if ac nbr correct and malloc for scene succcessful
// initianize need_loop and the default height and width
//then call the check file, scene bezeroed in check file
static t_scene	*precheck_av(int ac, char **av)
{
	t_scene	*scene;

	if (ac != 2)
	{
		ft_putstr_fd("Error: wrong argument nbr\n", 2);
		return (NULL);
	}
	scene = ft_calloc(1, sizeof(t_scene));
	if (scene == NULL)
	{
		ft_putstr_fd("Error: malloc scene failed\n", 2);
		return (NULL);
	}
	if (check_file(av, scene) == false)
	{
		free(scene);
		return (NULL);
	}
	scene->width = WIDTH;
	scene->height = HEIGHT;
	scene->need_loop = true;
	scene->running = true;
	return (scene);
}

//call check av firsr, then get each line and check and parse eachline'
// return the parsed scene to the main
// if error occured during one line. free evertyihg so far and return null
t_scene	*parsing(int ac, char **av)
{
	char	*line;
	t_scene	*scene;

	scene = precheck_av(ac, av);
	if (!scene)
		return (NULL);
	while (1)
	{
		line = get_next_line(scene->fd);
		if (!line)
			break ;
		normalize_line(line);
		if (!validating_parsing_line(line, scene))
			scene->line_error = true;
		free (line);
	}
	if (scene->line_error == true)
	{
		ft_putstr_fd("Error: error occured during line checking", 2);
		ft_free_scene(scene);
		return (NULL);
	}
	return (scene);
}
