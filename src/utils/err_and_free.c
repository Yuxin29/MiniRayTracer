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
static void ft_free_objects(t_scene *scene)
{
    if (scene->sp) //should be a linked list
    {
        free(scene->sp);
        scene->sp = NULL;
    }
    // if (scene->pl)
    // {
    //     free(scene->pl);
    //     scene->pl = NULL;
    // }
    // if (scene->cl)
    // {
    //     free(scene->cl);
    //     scene->cl = NULL;
    // }
}

void ft_free_scene(t_scene *scene)
{
    if (!scene)
        return;
    if (scene->ambient_light)
        free(scene->ambient_light);
    if (scene->cam)
        free(scene->cam);
    // if (scene->light)
    //     free(scene->light);
    ft_free_objects(scene);
    free(scene);
}