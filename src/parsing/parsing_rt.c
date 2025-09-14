#include "miniRT.h"
#include "parsing.h"


//check if file suffix valid // open file successful
static bool check_file(char **av, t_scene *scene)
{
	char	*ext;
	
	ft_bzero(scene, sizeof(t_scene));
	
	ext = ft_strrchr(av[1], '.');
    if (!ext || ft_strcmp(ext, ".rt") != 0)
    {
        ft_putstr_fd("wrong format\n", 1);
        return (false);
    }
	scene->fd = open(av[1], O_RDONLY);
    if (scene->fd == -1)
    {
        ft_putstr_fd("open file failed\n", 1);
        return (false);
    }
	return (true);
}

//check if ac nbr correct and malloc for scene succcessful
//then call the check file
static t_scene *precheck_av(int ac, char **av)
{
    t_scene *scene;

    if (ac < 2)
    {
        ft_putstr_fd("missing file argument\n", 1);
        return (NULL);
    }
    scene = malloc(sizeof(t_scene));
    if (!scene)
    {
        ft_putstr_fd("malloc scene failed\n", 1);
        return (NULL);
    }
    if (!check_file(av, scene))
    {
        free(scene);
        return (NULL);
    }
    return (scene);
}

//call check av firsr, then get each line and check and parse eachline'
// return the parsed scene to the main
// if error occured during one line. free evertyihg so far and return null
t_scene *parsing(int ac, char **av)
{
	char	*raw_line;
	char	*line;
	t_scene *scene;

    scene = precheck_av(ac, av);
	if (!scene)
		return (NULL);
	while (1)
	{
        raw_line = get_next_line(scene->fd);
		if (!raw_line)
			break ;
		line = ft_strtrim(raw_line, "\n"); //might be other change line, need to null check
        free (raw_line);
        if (!line)
        {
            ft_free_scene(scene);
			close(scene->fd);
			return (NULL);
        }
        if (line[0] && !validating_parsing_line(line, scene))
		{
			ft_putstr_fd("invalid line in the file", 1);
            printf("%s\n", line);
			free(line);
			ft_free_scene(scene);
			close(scene->fd);
			return (NULL);
		}
		free (line);
	}
	close(scene->fd);
	return (scene);
}
