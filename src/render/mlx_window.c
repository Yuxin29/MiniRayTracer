#include	"miniRT.h"
#include	"render.h"
#include	"parsing.h"

//lin needs to uses this ??
// this is probably where our work overlapping each other
// I write this prototype here just as a starting point
// the color of each pixel will be calulated by lin
//0xAAFF1111, Transparency + rgb
static void	render_scene(t_scene *scene)
{
	int				x;
	int				y;
	t_render_data	data;

	init_viewport(scene, &data.view); //yuxin added flexible size
	y = 0;
	while (y < scene->height)
	{
		x = 0;
		while (x < scene->width)
		{
			data.ray = generate_primary_ray(x, y, &data.view, scene);
			if (hit_objects(data.ray, scene->objects, &data.rec))
			{
				data.c = final_color(scene, data.rec);
				mlx_put_pixel(scene->img, x, y, (data.c.r << 24 | data.c.g << 16 | data.c.b << 8 | 255));
			}
			else
				mlx_put_pixel(scene->img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

// yuxin added this one,
// to call render_scene repeatedly if the keyboard as pressed some valid buttoms
static void render_scene_loop(void *param)
{
    t_scene *scene = (t_scene *)param;

	if (scene->need_loop)
	{
		render_scene(scene);
		scene->need_loop = false;
	}
}

//handling resizing
// incase of resizing, update the scene width and height can recall render scene
static void	handle_screen_resize(int32_t width, int32_t height, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
    mlx_delete_image(scene->mlx, scene->img);
    scene->img = mlx_new_image(scene->mlx, width, height);
    if (!scene->img)
    {
        ft_putstr_fd("mlx_new_image failed on resize\n", 2);
        return;
    }
    mlx_image_to_window(scene->mlx, scene->img, 0, 0);
	scene->width = width;
    scene->height = height;
	render_scene(scene);
}

//mlx_init: 4th: full scree> true or false
bool	mlx_window(t_scene *scene)
{
	scene->mlx = mlx_init(WIDTH, HEIGHT, "miniRT_test", true);
	if (!scene->mlx)
    {
        ft_putstr_fd("mlx_init failed\n", 1);
        return (false);
    }
	scene->img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
    if (!scene->img)
	{
        ft_putstr_fd("mlx_new image failed\n", 1);
        return (false);
    }
	mlx_image_to_window(scene->mlx, scene->img, 0, 0);

    mlx_key_hook(scene->mlx, key_hook, scene); //Keyboard press/release
	mlx_resize_hook(scene->mlx, handle_screen_resize, scene); //resizeing by mouse
	mlx_close_hook(scene->mlx, close_window, scene);  //clicking red x

	mlx_loop_hook(scene->mlx, render_scene_loop, scene);
	mlx_loop(scene->mlx);

	return (true);
}
