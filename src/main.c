#include "miniRT.h"
#include "parsing.h"
#include    "render.h"


//test printing delete alter
//=======================================================

void ft_print_scene(t_scene *scene)
{
	t_sphere *cur;
	int i = 1;

	printf("\n===== TEST PRINTING SCENE =====\n");

	// Ambient Light
	if (scene->ambient_light)
	{
		printf("Ambient Light:\n");
		printf("  ratio: %.2f\n", scene->ambient_light->ratio);
		printf("  color: R=%d G=%d B=%d\n",
			scene->ambient_light->rgb.r,
			scene->ambient_light->rgb.g,
			scene->ambient_light->rgb.b);
	}
	else
		printf("Ambient Light: (null)\n");

	// Camera
	if (scene->cam)
	{
		printf("Camera:\n");
		printf("  position: x=%.2f y=%.2f z=%.2f\n",
			scene->cam->v_point.x,
			scene->cam->v_point.y,
			scene->cam->v_point.z);
		printf("  orientation: x=%.2f y=%.2f z=%.2f\n",
			scene->cam->v_orien.x,
			scene->cam->v_orien.y,
			scene->cam->v_orien.z);
		printf("  FOV: %.2f\n", scene->cam->fov);
	}
	else
		printf("Camera: (null)\n");

	// Spheres
	cur = scene->sp;
	if (!cur)
		printf("Spheres: (none)\n");
	else
	{
		printf("Spheres (%d):\n", scene->sp_nbr);
		while (cur)
		{
			printf("  Sphere %d:\n", i++);
			printf("    center: x=%.2f y=%.2f z=%.2f\n",
				cur->sp_center.x, cur->sp_center.y, cur->sp_center.z);
			printf("    diameter: %.2f (radius: %.2f)\n",
				cur->dia, cur->radius);
			printf("    color: R=%d G=%d B=%d\n",
				cur->rgb.r, cur->rgb.g, cur->rgb.b);
			cur = cur->next;
		}
	}

	// MLX info
	printf("MLX:\n");
	printf("  mlx ptr : %p\n", (void *)scene->mlx);
	printf("  img ptr : %p\n", (void *)scene->img);

	printf("===== END OF SCENE PRINT =====\n\n");
}


//=======================================================

//test version for compiling
int main(int ac, char **av)
{
	t_scene	*scene;
	
    //parsing
    scene = parsing(ac, av);
	if (!scene)
		return(-1); //erro msg sent in parsing
	
    // mlx
	if (!mlx_window(scene))
		return(err_msg_code("mlx initiation failed\n", -1));
	
        //cleaning up and exit
	ft_print_scene(scene);
	ft_free_scene(scene);
	
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
