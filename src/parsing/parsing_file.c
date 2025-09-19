#include "miniRT.h"
#include "parsing.h"

//sub 
// Your program must take as a first argument 
// a scene description file with the .rt extension.
//check if file suffix valid // open file successful
static bool	check_file(char **av, t_scene *scene)
{
	char	*ext;

	ft_bzero(scene, sizeof(t_scene));
	ext = ft_strrchr(av[1], '.');
	if (!ext || ft_strcmp(ext, ".rt") != 0)
	{
		ft_putstr_fd("Error: wrong format\n", 1);
		return (false);
	}
	scene->fd = open(av[1], O_RDONLY);
	if (scene->fd == -1)
	{
		ft_putstr_fd("Error: open file failed\n", 1);
		return (false);
	}
	return (true);
}

//check if ac nbr correct and malloc for scene succcessful
// initianize need_loop and the default height and width
//then call the check file
static t_scene	*precheck_av(int ac, char **av)
{
	t_scene	*scene;

	if (ac < 2)
	{
		ft_putstr_fd("Error: missing file argument\n", 1);
		return (NULL);
	}
	scene = malloc(sizeof(t_scene));
	if (!scene)
	{
		ft_putstr_fd("Error: malloc scene failed\n", 1);
		return (NULL);
	}
	if (!check_file(av, scene))
	{
		free(scene);
		return (NULL);
	}
	scene->width = WIDTH;
	scene->height = HEIGHT;
	scene->need_loop = true;
	scene->running = true;
	// scene->al_existence = false;
	// scene->c_existence = false;
	// scene->l_existence = false;
	return (scene);
}

// in case of error happening in one the the line,
// print error msg and the error line
// free the line and screen
static t_scene	*dealing_line_err(t_scene *scene)
{
	ft_putstr_fd("Error: Invalid line in the file: ", 1);
	ft_putchar_fd('\n', 1);
	ft_free_scene(scene);
	return (NULL);
}

//call check av firsr, then get each line and check and parse eachline'
// return the parsed scene to the main
// if error occured during one line. free evertyihg so far and return null
t_scene	*parsing(int ac, char **av)
{
	char	*raw_line;
	char	*line;
	t_scene	*scene;

	scene = precheck_av(ac, av);
	if (!scene)
		return (NULL);
	while (1)
	{
		raw_line = get_next_line(scene->fd);
		if (!raw_line)
			break ;
		line = ft_strtrim(raw_line, "\t\r\n");
		free (raw_line);
		if (!line)
		{
			ft_free_scene(scene);
			return (NULL);
		}
		if (!validating_parsing_line(line, scene))
			scene->line_error = true;
		free (line);
	}
	if (scene->line_error == true)
		return (dealing_line_err(scene));
	return (scene);
}
