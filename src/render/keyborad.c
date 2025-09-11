// #include    "render.h"

// //this checks the move and if it is valid, and what kind of move it is,
// void	keyboard_control(mlx_key_data_t	keydata, void *param)
// {
// 	t_map	*mp;
// 	int		x_new;
// 	int		y_new;

// 	if (keydata.action != MLX_PRESS)
// 		return ;
// 	mp = (t_map *)param;
// 	if (keydata.key == MLX_KEY_ESCAPE)
// 	{
// 		mlx_close_window(mp->mlx);
// 		ft_putstr_fd("You quited by ESC\n", 1);
// 		return ;
// 	}
// 	else
// 		return ;
// 	move(mp, x_new, y_new);
// }