#include "miniRT.h"


/**
 * @brief 	Delete mlx instance and image
 * @param 	*t_scene scene pointer to the scene struct
 * @return void	
 *
 */
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


/**
 * @brief 	Free the scene struct and its contents		
 * @param 	*t_scene scene pointer to the scene struct
 * @return void
 *
 * @note called when error occurs during parsing or at the end of the program
 */
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

/**
 * @brief 	Check if the file is valid and open it
 * @param 	**av array of arguments
 * @param 	*t_scene scene pointer to the scene struct
 * @return bool true if file is valid and opened, false otherwise
 *
 * @note check if the file has .rt extension and read only permission
 */
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

/**
 * @brief 	Precheck the arguments, malloc scene and check file, set default values of scene
 * @param 	ac number of arguments
 * @param 	**av array of arguments
 * @return t_scene* pointer to the parsed scene or NULL if error
 *
 * @note 	If the number of arguments is not correct, or if malloc fails, or if file check fails, return NULL
 */
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

/**
 * @brief 	Parsing the .rt file
 * @param 	ac number of arguments
 * @param 	**av array of arguments
 * @return t_scene* pointer to the parsed scene or NULL if error
 *
 * @note call precheck av first, then get each line and check and parse eachline
 *       if error occured during one line. free evertyihg so far and return null
 */
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
	if (scene->line_error == true || !scene->al_existence
		|| !scene->c_existence || !scene->l_existence)
	{
		ft_putstr_fd("Error: error occured during line checking\n", 2);
		ft_free_scene(scene);
		return (NULL);
	}
	return (scene);
}
