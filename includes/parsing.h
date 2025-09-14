#ifndef PARSING_H
# define PARSING_H

//headers
#include "miniRT.h"
#include "utils.h"

//libs
#include <fcntl.h>      //open
#include <stdio.h>      //printf for testing

//struct
typedef struct s_color
{
    int     r;
    int     g;
    int     b;
}	t_color;

// Ambient lightning:
// A 0.2 255,255,255
// ∗ identifier: A
// ∗ ambient lighting ratio in range [0.0,1.0]: 0.2
// ∗ R,G,B colors in range [0-255]: 255, 255, 255
typedef struct s_a_light
{
	float	ratio;
	t_color	rgb;
}			t_a_light;

// ◦ Camera:
// C -50.0,0,20 0,0,1 70
// ∗ identifier: C
// ∗ x,y,z coordinates of the view point: -50.0,0,20
// ∗ 3d normalized orientation vector.
// In range [-1,1] for each x,y,z axis:
// 0.0,0.0,1.0
// ∗ FOV : Horizontal field of view in degrees in range [0,180]: 70
typedef struct s_camera
{
	t_vec3	v_point;
	t_vec3	v_orien;
	float	fov; //lin modify
}	t_camera;

// ◦ Light:
// L -40.0,50.0,0.0 0.6 10,0,255
// ∗ identifier: L
// ∗ x,y,z coordinates of the light point: -40.0,50.0,0.0
// ∗ the light brightness ratio in range [0.0,1.0]: 0.6
// ∗ (unused in mandatory part)
// R,G,B colors in range [0-255]: 10, 0, 255
typedef struct s_light
{
	t_vec3	l_point;
	float	br_ratio;
	//t_color rgb;
}	t_light;

// ◦ Sphere:
// sp 0.0,0.0,20.6 12.6 10,0,255
// ∗ identifier: sp
// ∗ x,y,z coordinates of the sphere center: 0.0,0.0,20.6
// ∗ the sphere dmeter: 12.6
// ∗ R,G,B colors in range [0-255]: 10, 0, 255
typedef struct s_sphere t_sphere;

typedef struct s_sphere
{
	t_vec3		sp_center;
	float		dia;
	float		radius; // lin modify
	t_color		rgb;
	t_sphere	*next;
}				t_sphere;

// ◦ Plane:
// pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
// ∗ identifier: pl
// ∗ x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
// ∗ 3d normalized normal vector. 
// In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
// ∗ R,G,B colors in range [0-255]: 0,0,225
typedef struct s_plane t_plane;

typedef struct s_plane
{
	t_vec3		p_in_pl;
	t_vec3		nor_v;
	t_color		rgb;
	t_plane		*next;
}	t_plane;

// ◦ Cylinder:
// cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
// ∗ identifier: cy
// ∗ x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
// ∗ 3d normalized vector of axis of cylinder. 
// In range [-1,1] for each x,y,z axis:0.0,0.0,1.0
// ∗ the cylinder diameter: 14.2
// ∗ the cylinder height: 21.42
// ∗ R,G,B colors in range [0,255]: 10, 0, 255
typedef struct s_cylinder t_cylinder;

typedef struct s_cylinder
{
	t_vec3		cy_center;
	t_vec3		cy_axis;
	float		dia;
	float		radius;
	float		height;
	t_color		rgb;
	t_cylinder	*next;
}				t_cylinder;

// a ascene with everything inside
typedef struct s_scene
{
	int			fd;
	t_a_light	ambient_light;
	t_camera	cam;
	t_light		light;
	t_sphere	*sp;
	int			sp_nbr;
	t_plane		*pl;
	int			pl_nbr;
	t_cylinder	*cl;
	int			cl_nbr;
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_scene;

//parsing_rt.c          3/5
t_scene	*parsing(int ac, char **av);

//parsing_line.c        4/5
bool	validating_parsing_line(char *line, t_scene *scene);

// parsing_env.c     3/5
// parsing lights and camera:
bool	validate_parsing_tokens_a(char **tokens, t_scene *scene);
bool	validate_parsing_tokens_c(char **tokens, t_scene *scene);
bool	validate_parsing_tokens_l(char **tokens, t_scene *scene);

//parsing_obj.c     3/5
// parsing objects: sphere, plane and cylinder
bool	validate_parsing_tokens_sp(char **tokens, t_scene *scene);
bool	validate_parsing_tokens_pl(char **tokens, t_scene *scene);
bool	validate_parsing_tokens_cy(char **tokens, t_scene *scene);

//parsing_utils_1.c   3/5
float	ft_atoi_float(char *str);
int		count_token_nbr(char **tokens);
void	free_three_arr(char **vec_1, char **vec_2, char **colors);

//parsing_utils_2.c   5/5
bool	do_color(char **colors, t_color *rgb);
bool	do_normalized_vectoy(char **vec, t_vec3 *vec_nor);
bool	check_valid_float(char *vec);
bool	do_xyz_vectoy(char **vec, t_vec3 *vec_xyz);

#endif
