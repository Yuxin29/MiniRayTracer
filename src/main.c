#include "miniRT.h"
#include "parsing.h"

//test version for compiling
int main(int ac, char **av)
{
	t_scene	*scene;
	
	scene = malloc(sizeof(t_scene));
	if (!scene)
		return(err_msg_code("malloc scene failed\n", -1));
	ft_bzero(scene, sizeof(t_scene));
	if (!parsing(ac, av, scene))
		return(err_msg_code("parsing failed\n", -1));

	//test mlxlib
	mlx_t		*mlx_window;
    mlx_image_t *mlx_image;

	mlx_window = mlx_init(720, 480, "miniRT_test", false);
	mlx_image = mlx_new_image(mlx_window, 480, 720);
	mlx_image_to_window(mlx_window, mlx_image, 0, 0);
	mlx_put_pixel(mlx_image, 0, 0, 0xAABBCCAA);
	mlx_loop(mlx_window);                       	
	mlx_terminate(mlx_window);
	return (0);
}

