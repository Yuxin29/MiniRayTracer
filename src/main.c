#include "miniRT.h"

#define WIDTH 800 //test
#define HEIGHT 600 //test

void	hook(void *param)
{
	mlx_t	*mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int	main(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
		return (EXIT_FAILURE);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
