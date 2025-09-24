#include "miniRT.h"
#include "parsing.h"

// Clicking on the red cross on the window’s frame
// must close the window and quit the program cleanly.
void	close_window(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	scene->running = false;
}

static void	move_keys(mlx_key_data_t keydata, t_scene *scene)
{
	t_vec3	move;
	float	move_unit;

	move = (t_vec3){0, 0, 0};
	move_unit = 1.0;
	if (keydata.key == MLX_KEY_W)
		move = (t_vec3){0, move_unit, 0};
	if (keydata.key == MLX_KEY_S)
		move = (t_vec3){0, -move_unit, 0};
	if (keydata.key == MLX_KEY_A)
		move = (t_vec3){move_unit, 0, 0};
	if (keydata.key == MLX_KEY_D)
		move = (t_vec3){-move_unit, 0, 0};
	if (vec_len(move))
	{
		scene->need_loop = 1;
		change_move(scene, move);
	}
}

static void	scale_keys(mlx_key_data_t keydata, t_scene *scene)
{
	float	scale;

	scale = 0;
	if (keydata.key == MLX_KEY_UP)
		scale = 1.2;
	if (keydata.key == MLX_KEY_DOWN)
		scale = 0.8;
	if (scale != 0)
	{
		scene->need_loop = 1;
		change_scale(scene, scale);
	}
}

// we assume the rotate always happengin around the vertical axit
static void	rotate_keys(mlx_key_data_t keydata, t_scene *scene)
{
	t_vec3	y_axis;

	y_axis = (t_vec3){0, 1, 0};
	if (keydata.key == MLX_KEY_LEFT)
	{
		scene->need_loop = 1;
		change_rotation(scene, y_axis, -0.3);
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		scene->need_loop = 1;
		change_rotation(scene, y_axis, 0.3);
	}
}

//Pressing ESC must close the window and quit the program cleanly.
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		close_window(scene);
	move_keys(keydata, scene);
	scale_keys(keydata, scene);
	rotate_keys(keydata, scene);
}
