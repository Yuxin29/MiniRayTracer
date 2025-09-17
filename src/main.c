#include	"miniRT.h"
#include "parsing.h"
#include    "render.h"

// //test version for compiling

int main(int ac, char **av)
{
	t_scene	*scene;

    //parsing
    scene = parsing(ac, av);
	if (!scene)
		return(-1); //erro msg sent in parsing

	//remove later
	//ft_print_scene(scene); //testing. remove later

	// // mlx
	if (!mlx_window(scene))
	{
		ft_putstr_fd("mlx initiation failed\n", 1);
		return (-1);
	}
    return (0);
}

//==========================lin test===========================
// void	add_object(t_object **list, t_obj_type type, void *data)
// {
// 	t_object	*new;

// 	new = malloc(sizeof(t_object));
// 	if (!new)
// 		return ;
// 	new->type = type;
// 	new->data = data;
// 	new->next = *list;
// 	*list = new;
// }

// void	setup_scene(t_scene *scene)
// {
// 	t_sphere *s = malloc(sizeof(t_sphere));
// 	s->sp_center = vec3(0, 0, -5);
// 	s->radius = 1.0f;
// 	s->rgb = (t_color){255, 0, 0};
// 	add_object(&scene->objects, OBJ_SP, s);
// }

// int	main(void)
// {
// 	t_scene			scene;

// 	scene.mlx = mlx_init(WIDTH, HEIGHT, "miniRT", false);
// 	scene.img = mlx_new_image(scene.mlx, WIDTH, HEIGHT);
// 	scene.objects = NULL;

// 	scene.cam.v_point = vec3(0, 0, 0);
// 	scene.cam.v_orien = vec3(0, 0, -1);
// 	scene.cam.fov = 70;
// 	scene.ambient_light.ratio = 0.5f;
// 	scene.ambient_light.rgb = (t_color){220, 20, 180};
// 	scene.light.br_ratio = 0.8f;
// 	scene.light.l_point = vec3(10, 20, 0);
// 	scene.light.rgb = (t_color){250, 20, 35};
// 	setup_scene(&scene);

// 	render_scene(&scene);

// 	mlx_image_to_window(scene.mlx, scene.img, 0, 0);
// 	mlx_loop(scene.mlx);
// 	mlx_terminate(scene.mlx);
// 	return (0);
// }

// test printing delete alter
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
// //=======================================================


