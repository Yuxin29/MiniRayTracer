#ifndef RENDER_H
# define RENDER_H

typedef struct s_scene t_scene;

//self_defined header
# include "../libft/libft.h"
#include "MLX42/MLX42.h"
#include "miniRT.h"
#include "parsing.h"

// //keyboard.c
// int err_msg_code(char *str, int n);
// void    ft_free_scene(t_scene *scene);

//mlx_window.c
int	mlx_window(t_scene *scene);

#endif