#include "miniRT.h"

/**
 * @brief 	Main function
 *
 * @param 	ac 
 * @param 	**av	
 * @example	./miniRT scene.rt
 * @return int as a exit code
 *
 * @note If any misconfiguration of any kind is encountered in the file the program must exit properly and return "Error\n"	
 *		 followed by an explicit error message of your choice.	
 */
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
