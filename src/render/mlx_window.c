#include "miniRT.h"

// camera updated inside it, be called repeately
//0xAAFF1111, Transparency + rgb
static void	render_scene(t_scene *scene)
{
	int				x;
	int				y;
	t_render_data	data;

	init_viewport(scene, &data.view);
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
				mlx_put_pixel(scene->img, x, y,
					(data.c.r << 24 | data.c.g << 16 | data.c.b << 8 | 255));
			}
			else
				mlx_put_pixel(scene->img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

// call render_scene repeatedly if the keyboard / mousing chaning scene
static void	render_scene_loop(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (!scene->running)
	{
		ft_free_scene(scene);
		exit (0);
	}
	if (scene->need_loop)
	{
		render_scene(scene);
		scene->need_loop = false;
	}
}

// sub:
// When you change the resolution of the window,
// the content of the window must remain unchanged and be adjusted accordingly.
// inplementation:
// incase of resizing, update the scene width and height
// and can recall render scene repeatedly
static void	handle_screen_resize(int32_t width, int32_t height, void *param)
{
	t_scene		*scene;
	mlx_image_t	*new;

	scene = (t_scene *)param;
	new = mlx_new_image(scene->mlx, width, height);
	if (!new)
	{
		ft_putstr_fd("Error: resize: mlx_new_image failed\n", 2);
		return ;
	}
	if (scene->img)
		mlx_delete_image(scene->mlx, scene->img);
	scene->img = new;
	mlx_image_to_window(scene->mlx, scene->img, 0, 0);
	scene->width = width;
	scene->height = height;
	scene->need_loop = true;
}

//mlx_init: 4th: full scree> true or false
// mlx_key_hook(scene->mlx, key_hook, scene); //Keyboard press/release
// mlx_resize_hook(scene->mlx, handle_screen_resize, scene);
//resizeing by mouse
// mlx_close_hook(scene->mlx, close_window, scene);  //clicking red x
bool	mlx_window(t_scene *scene)
{
	scene->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!scene->mlx)
	{
		ft_putstr_fd("Error: mlx_init failed\n", 2);
		return (false);
	}
	scene->img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	if (!scene->img)
	{
		ft_putstr_fd("Error: mlx_new image failed\n", 2);
		return (false);
	}
	mlx_image_to_window(scene->mlx, scene->img, 0, 0);
	mlx_key_hook(scene->mlx, key_hook, scene);
	mlx_close_hook(scene->mlx, close_window, scene);
	mlx_resize_hook(scene->mlx, handle_screen_resize, scene);
	mlx_loop_hook(scene->mlx, render_scene_loop, scene);
	while (scene->running)
		mlx_loop(scene->mlx);
	ft_free_scene(scene);
	return (true);
}
