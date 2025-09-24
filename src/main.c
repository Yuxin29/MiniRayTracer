#include "miniRT.h"
#include "parsing.h"

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

// =======================================================
// void	ft_print_scene(t_scene *scene)
// {
// 	t_object	*tmp;
// 	int			i;

// 	printf("\n===== TEST PRINTING SCENE =====\n");

// 	// Ambient Light
// 	printf("Ambient Light:\n");
// 	printf("  ratio: %.2f\n", scene->ambient_light.ratio);
// 	printf("  color: R=%d G=%d B=%d\n",
// 		scene->ambient_light.rgb.r,
// 		scene->ambient_light.rgb.g,
// 		scene->ambient_light.rgb.b);

// 	// Camera
// 	printf("Camera:\n");
// 	printf("  position: x=%.2f y=%.2f z=%.2f\n",
// 		scene->cam.v_point.x,
// 		scene->cam.v_point.y,
// 		scene->cam.v_point.z);
// 	printf("  orientation: x=%.2f y=%.2f z=%.2f\n",
// 		scene->cam.v_orien.x,
// 		scene->cam.v_orien.y,
// 		scene->cam.v_orien.z);
// 	printf("  FOV: %.2f\n", scene->cam.fov);

// 	// Light
// 	printf("Light:\n");
// 	printf("  light point: x=%.2f y=%.2f z=%.2f\n",
// 		scene->light.l_point.x,
// 		scene->light.l_point.y,
// 		scene->light.l_point.z);
// 	printf("  brightness ratio: %.2f\n", scene->light.br_ratio);

// 	// Objects
// 	tmp = scene->objects;
// 	if (!tmp)
// 		printf("Objects: (none)\n");
// 	else
// 	{
// 		i = 1;
// 		printf("Objects:\n");
// 		while (tmp)
// 		{
// 			if (tmp->type == OBJ_SP)
// 			{
// 				t_sphere *sp = (t_sphere *)tmp->data;
// 				printf("  Sphere %d:\n", i++);
// 				printf("    center: x=%.2f y=%.2f z=%.2f\n",
// 					sp->sp_center.x, sp->sp_center.y, sp->sp_center.z);
// 				printf("    radius: %.2f\n", sp->radius);
// 				printf("    color: R=%d G=%d B=%d\n",
// 					sp->rgb.r, sp->rgb.g, sp->rgb.b);
// 			}
// 			else if (tmp->type == OBJ_PL)
// 			{
// 				t_plane *pl = (t_plane *)tmp->data;
// 				printf("  Plane %d:\n", i++);
// 				printf("    point: x=%.2f y=%.2f z=%.2f\n",
// 					pl->p_in_pl.x, pl->p_in_pl.y, pl->p_in_pl.z);
// 				printf("    normal: x=%.2f y=%.2f z=%.2f\n",
// 					pl->nor_v.x, pl->nor_v.y, pl->nor_v.z);
// 				printf("    color: R=%d G=%d B=%d\n",
// 					pl->rgb.r, pl->rgb.g, pl->rgb.b);
// 			}
// 			else if (tmp->type == OBJ_CY)
// 			{
// 				t_cylinder *cy = (t_cylinder *)tmp->data;
// 				printf("  Cylinder %d:\n", i++);
// 				printf("    center: x=%.2f y=%.2f z=%.2f\n",
// 					cy->cy_center.x, cy->cy_center.y, cy->cy_center.z);
// 				printf("    axis: x=%.2f y=%.2f z=%.2f\n",
// 					cy->cy_axis.x, cy->cy_axis.y, cy->cy_axis.z);
// 				printf("    radius: %.2f height: %.2f\n",
// 					cy->radius, cy->height);
// 				printf("    color: R=%d G=%d B=%d\n",
// 					cy->rgb.r, cy->rgb.g, cy->rgb.b);
// 			}
// 			tmp = tmp->next;
// 		}
// 	}

// 	// MLX info
// 	printf("MLX:\n");
// 	printf("  mlx ptr : %p\n", (void *)scene->mlx);
// 	printf("  img ptr : %p\n", (void *)scene->img);

// 	printf("===== END OF SCENE PRINT =====\n\n");
// }
