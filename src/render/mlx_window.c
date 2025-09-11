#include    "miniRT.h"
#include    "render.h"
#include    "parsing.h"

//lin needs to uses this
//0xAAFF1111, Transparency, ^rgb
void render_scene(t_scene *scene)
{
    int x;
    int y;

    x = 0;
    while (x < WIDTH)
    {
        y = 0;
        while (y < HEIGHT)
        {
            mlx_put_pixel(scene->img, x, y, 0xAAFF1111);
            y++;
        }
        x++;
    }
}
//remove to render later
int	mlx_window(t_scene *scene)
{
	//this part need to take out later
	scene->mlx = mlx_init(WIDTH, HEIGHT, "miniRT_test", false);
	if (!scene->mlx)
   		return(err_msg_code("mlx_init failed\n", 0));
	scene->img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(scene->mlx, scene->img, 0, 0);
	render_scene(scene);
	mlx_loop(scene->mlx);                       	
	//mlx_terminate(scene->mlx);
	return (1);
}