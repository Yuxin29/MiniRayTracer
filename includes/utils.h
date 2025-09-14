#ifndef UTILS_H
# define UTILS_H

//headers
# include "../libft/libft.h"
#include "parsing.h"
#include "miniRT.h"

typedef struct s_scene t_scene;

//err_and_free.c
int     err_msg_code(char *str, int n);
void    ft_free_scene(t_scene *scene);


#endif