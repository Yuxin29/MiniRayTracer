#include "miniRT.h"
#include "parsing.h"
#include    "render.h"


//test printing delete alter
//=======================================================

void    ft_print_scene(t_scene *scene)
{
    t_sphere *cur;

    printf("\n===== TEST PRINTING SCENE =====\n");

    if (scene->ambient_light)
    {
        printf("Ambient Light:\n");
        printf("  ratio: %.2f\n", scene->ambient_light->ratio);
        printf("  color: R=%d G=%d B=%d\n",
            scene->ambient_light->r,
            scene->ambient_light->g,
            scene->ambient_light->b);
    }
    else
        printf("Ambient Light: (null)\n");

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
        printf("  FOV: %d\n", scene->cam->fov);
    }
    else
        printf("Camera: (null)\n");

    cur = scene->sp;
    if (!cur)
        printf("Spheres: (none)\n");
    else
    {
        int i = 1;
        while (cur)
        {
            printf("Sphere %d:\n", i++);
            printf("  center: x=%.2f y=%.2f z=%.2f\n",
                cur->sp_center.x, cur->sp_center.y, cur->sp_center.z);
            printf("  diameter: %.2f\n", cur->dia);
            printf("  color: R=%d G=%d B=%d\n", cur->r, cur->g, cur->b);
            cur = cur->next;
        }
    }

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
	
	//malloc
	scene = malloc(sizeof(t_scene));
	if (!scene)
		return(err_msg_code("malloc scene failed\n", -1));
	ft_bzero(scene, sizeof(t_scene));
	//parsing
	if (!parsing(ac, av, scene))
		return(-1); //erro msg sent in parsing
	// mlx
	if (!mlx_window(scene))
		return(err_msg_code("mlx initiation failed\n", -1));
	//cleaning up and exit
	ft_print_scene(scene);
	ft_free_scene(scene);
	return (0);
}
