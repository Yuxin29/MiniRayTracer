#include "miniRT.h"

// subjects
// If any misconfiguration of any kind is encountered in the file
// the program must exit properly and return "Error\n"
// followed by an explicit error message of your choice.
// subjects
// in case of errors, msg sent in sice parsing and mlx
// scene malloced and inited within parsing
// mlx inited within mlx wendow
// ft_print_scene(scene); //testing, betwenn parsing and mlx
int	main(int ac, char **av)
{
	t_scene	*scene;

	scene = parsing(ac, av);
	if (scene == NULL)
		return (-1);
	if (mlx_window(scene) == false)
	{
		ft_free_scene(scene);
		return (-1);
	}
	return (0);
}
