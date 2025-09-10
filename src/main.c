// #inlcude "minirt.h"
//#include "so_long.h"

//remove to .h later
#include <fcntl.h>
#include <stdio.h>

//test we should do in day 1
// mlx_init(width, height, "title", true)	//open a winder
// mlx_new_image(mlx, width, height)	    //创建一张可操作的图像	了解如何拿到 mlx_image_t *
// mlx_image_to_window(mlx, image, x, y)	//把 image 显示到窗口	知道它是怎么把画布放上去的
// mlx_put_pixel(image, x, y, color)	    //在 image 上画像素	学会怎么画一个点
// mlx_loop(mlx)                        	//进入渲染循环	明白主循环的概念
// mlx_terminate(mlx)	                    //释放所有资源并退出	知道如何干净退出

//test version for compiling
int main(int ac, char **av)
{
	if (ac != 2)
		return (-1);

    //test get_next_line
	int fd = open(av[1], O_RDONLY);
	char   *line;
	line = get_next_line(fd);
	while (line)
	{
		printf("%s\n", line);
		free (line);
		line = get_next_line(fd);
	}

	//test mlxlib
	mlx_t		*mlx_window;
    mlx_image_t *mlx_image;

	mlx_window = mlx_init(720, 480, "miniRT_test", false);
	mlx_image = mlx_new_image(mlx_window, 480, 720);
	mlx_image_to_window(mlx_window, mlx_image, 0, 0);	//把 image 显示到窗口	知道它是怎么把画布放上去的
	// mlx_put_pixel(image, x, y, color)	    //在 image 上画像素	学会怎么画一个点
	mlx_loop(mlx_window);                       	
	mlx_terminate(mlx_window);
	return (0);
}