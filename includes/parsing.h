#ifndef PARSING_H
# define PARSING_H

#include "miniRT.h"


typedef struct s_color
{
    int     r;
    int     g;
    int     b;
}	t_color;

//struct
// Ambient lightning:
// A 0.2 255,255,255
// ∗ identifier: A
// ∗ ambient lighting ratio in range [0.0,1.0]: 0.2
// ∗ R,G,B colors in range [0-255]: 255, 255, 255
typedef struct s_a_light
{
    float   ratio;
    t_color rgb;
}	t_a_light;

// ◦ Camera:
// C -50.0,0,20 0,0,1 70
// ∗ identifier: C
// ∗ x,y,z coordinates of the view point: -50.0,0,20
// ∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
// 0.0,0.0,1.0
// ∗ FOV : Horizontal field of view in degrees in range [0,180]: 70
typedef struct s_camera
{
	t_vec3	v_point;
	t_vec3	v_orien;
	float	fov; //lin modify
}	t_camera;

//======================== maybe also later ============================
// ◦ Light:
// L -40.0,50.0,0.0 0.6 10,0,255
// ∗ identifier: L
// ∗ x,y,z coordinates of the light point: -40.0,50.0,0.0
// ∗ the light brightness ratio in range [0.0,1.0]: 0.6
// ∗ (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255

// ◦ Sphere:
// sp 0.0,0.0,20.6 12.6 10,0,255
// ∗ identifier: sp
// ∗ x,y,z coordinates of the sphere center: 0.0,0.0,20.6
// ∗ the sphere dmeter: 12.6
// ∗ R,G,B colors in range [0-255]: 10, 0, 255
typedef struct s_sphere t_sphere;

typedef struct s_sphere
{
	t_vec3  sp_center;
	float   dia;
	float	radius; // lin modify
	t_color rgb;
    t_sphere    *next;
}	t_sphere;

//======================== WEEK 2 ONLY ============================
// ◦ Plane:
// pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
// ∗ identifier: pl
// ∗ x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
// ∗ 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
// ∗ R,G,B colors in range [0-255]: 0,0,225

//======================== WEEK 2 ONLY ============================
// ◦ Cylinder:
// cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
// ∗ identifier: cy
// ∗ x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
// ∗ 3d normalized vector of axis of cylinder. In range [-1,1] for each x,y,z axis:
// 0.0,0.0,1.0
// ∗ the cylinder diameter: 14.2
// ∗ the cylinder height: 21.42
// ∗ R,G,B colors in range [0,255]: 10, 0, 255

typedef struct s_scene
{
    int         fd;
    t_a_light   *ambient_light;
    t_camera    *cam;
    // t_light   *light;
    t_sphere    *sp;
    int         sp_nbr;
    // t_pl        *pl;
    // int       pl_nbr;
    // t_cl        *cl;
    // int       cl_nbr;
    mlx_t       *mlx;
    mlx_image_t *img;
}	t_scene;

//headers
#include "utils.h"

//libs
#include <fcntl.h>      //open
#include <stdio.h>      //printf for testing

//parsing_rt.c          3/5
t_scene    *parsing(int ac, char **av);

//parsing_line.c        3/5
bool validating_parsing_line(char *line, t_scene *scene);

// parsing_env.c
bool    validate_parsing_tokens_a(char **tokens, t_scene *scene);
bool    validate_parsing_tokens_c(char **tokens, t_scene *scene);
bool    validate_parsing_tokens_l(char **tokens, t_scene *scene);

//parsing_obj.c     3/5
bool    validate_parsing_tokens_sp(char **tokens, t_scene *scene);
bool    validate_parsing_tokens_pl(char **tokens, t_scene *scene);
bool    validate_parsing_tokens_cy(char **tokens, t_scene *scene);

//parsing_utils_1.c   4/5
void    ft_filling_vec(char **str, t_vec3	*vec);
float	ft_atoi_float(char *str);
int	count_token_nbr(char **tokens);

//parsing_utils_2.c   3/5
bool check_rgb(char **colors);
void do_color(char **colors, t_color *rgb);

#endif
