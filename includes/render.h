#ifndef RENDER_H
# define RENDER_H

typedef struct s_scene t_scene;

typedef struct s_render_data
{
	t_ray			ray;
	t_camera_view	view;
	t_hit_record	rec;
	t_color			c;
}	t_render_data;

//self_defined header
# include "../libft/libft.h"
#include "MLX42/MLX42.h"
#include "miniRT.h"
#include "parsing.h"

//mlx_window.c
bool	mlx_window(t_scene *scene);
// keyboard.c
// close window by x and 3 types of keyboard controk
void	close_window(void *param);
void	key_hook(mlx_key_data_t keydata, void *param);
//move_and_rotate.c		4/5
void	change_move(t_scene *scene, t_vec3 move);
void	change_zoomin(t_scene *scene, float scale);
void	change_rotation(t_scene *scene, t_vec3 y_axis, float angle);

#endif

