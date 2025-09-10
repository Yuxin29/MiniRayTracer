#include "miniRT.h"

//test version for compiling
int main(int ac, char **av)
{
	if (!parsing(ac, av))
        return (-1);

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

// #define WIDTH 800 //test
// #define HEIGHT 600 //test

// void	hook(void *param)
// {
// 	mlx_t	*mlx = param;
// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// }

// int	main(void)
// {
// 	mlx_t	*mlx;

// 	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
// 	if (!mlx)
// 		return (EXIT_FAILURE);
// 	mlx_loop_hook(mlx, &hook, mlx);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }
