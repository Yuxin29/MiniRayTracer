#include "miniRT.h"
#include "parsing.h"


//test printing delete alter
//=======================================================
static void print_a_light(t_a_light *a)
{
    if (!a)
    {
        printf("Ambient light is NULL\n");
        return;
    }
    printf("Ambient Light:\n");
    printf("  ratio: %.2f\n", a->ratio);
    printf("  color: R=%d G=%d B=%d\n", a->r, a->g, a->b);
}

static void print_camera(t_camera *c)
{
    if (!c)
    {
        printf("Camera is NULL\n");
        return;
    }
    printf("Camera:\n");
    printf("  position: x=%.2f y=%.2f z=%.2f\n", c->v_point.x, c->v_point.y, c->v_point.z);
    printf("  orientation: x=%.2f y=%.2f z=%.2f\n", c->v_orien.x, c->v_orien.y, c->v_orien.z);
    printf("  FOV: %d\n", c->fov);
}

static void print_sphere(t_sphere *s)
{
    while (s)
    {
        printf("Sphere:\n");
        printf("  center: x=%.2f y=%.2f z=%.2f\n", s->sp_center.x, s->sp_center.y, s->sp_center.z);
        printf("  diameter: %.2f\n", s->dia);
        printf("  color: R=%d G=%d B=%d\n", s->r, s->g, s->b);
        s = s->next;
    }
}

static void ft_print_scene(t_scene *scene)
{
	//test print
	printf("\n\n%s\n", "test printing scene");
	if (scene->ambient_light)
		print_a_light(scene->ambient_light);
	if (scene->cam)
		print_camera(scene->cam);
	if (scene->sp)
		print_sphere(scene->sp);
}
//=======================================================


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

	ft_print_scene(scene);

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

