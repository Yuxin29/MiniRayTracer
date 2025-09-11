#include "utils.h"
#include "miniRT.h"
#include "parsing.h"

int err_msg_code(char *str, int n)
{
    if (str)
        ft_putstr_fd(str, 1);
    return (n);
}

//free linked list objects
static void ft_free_linked_objects(t_scene *scene)
{
    t_sphere *sp_tmp;
    // t_plane *pl_tmp;
    // t_cylinder *cy_tmp;

    if (scene->sp) //should be a linked list
    {
        sp_tmp = scene->sp->next; 
        free(scene->sp);
        scene->sp = sp_tmp;
    }
    scene->sp = NULL;
//      if (scene->pl) //should be a linked list
//     {
//         pl_tmp = scene->sp->next; 
//         free(scene->sp);
//         scene->sp = pl_tmp;
//     }
//     scene->pl = NULL;
//     if (scene->cy) //should be a linked list
//     {
//         cy_tmp = scene->sp->next; 
//         free(scene->sp);
//         scene->sp = cy_tmp;
//     }
//     scene->cy = NULL;
}

void ft_free_scene(t_scene *scene)
{
    ft_free_linked_objects(scene);
    if (!scene)
        return;
    if (scene->ambient_light)
        free(scene->ambient_light);
    if (scene->cam)
        free(scene->cam);
    // if (scene->light)  //not parsed yet
    //     free(scene->light);
    if (scene->img && scene->mlx)
        mlx_delete_image(scene->mlx, scene->img);
    if (scene->mlx)
        mlx_terminate(scene->mlx);
    free(scene);
}