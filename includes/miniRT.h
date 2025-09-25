#ifndef MINIRT_H
# define MINIRT_H

//self_defined header
# include "../libft/libft.h"
# include "MLX42/MLX42.h"

//lib headers
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>      //open 

# define WIDTH 800
# define HEIGHT 600
# define EPSILON 1e-2
# define _USE_MATH_DEFINES

/* ~~~~~~~~~~~~~~~~~~ TOOL STRUC ~~~~~~~~~~~~~~~~~~ */
typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_color;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

/* ~~~~~~~~~~~~~~~~~~ PARSING STRUC ~~~~~~~~~~~~~~~~~~ */
// Ambient lightning: A 0.2 255,255,255
// ∗ identifier: A
// ∗ ambient lighting ratio in range [0.0,1.0]: 0.2
// ∗ R,G,B colors in range [0-255]: 255, 255, 255
typedef struct s_a_light
{
	float	ratio;
	t_color	rgb;
}	t_a_light;

// ◦ Camera: C -50.0,0,20 0,0,1 70
// ∗ identifier: C
// ∗ x,y,z coordinates of the view point: -50.0,0,20
// ∗ 3d normalized orientation vector. In range [-1,1]: 0.0,0.0,1.0
// ∗ FOV : Horizontal field of view in degrees in range [0,180]: 70
typedef struct s_camera
{
	t_vec3	v_point;
	t_vec3	v_orien;
	float	fov;
}	t_camera;

// ◦ Light:  L -40.0,50.0,0.0 0.6 10, 0, 255
// ∗ identifier: L
// ∗ x,y,z coordinates of the light point: -40.0,50.0,0.0
// ∗ the light brightness ratio in range [0.0,1.0]: 0.6
// ∗ (unused in mandatory part) R,G,B colors in range [0-255]: 10, 0, 255
typedef struct s_light
{
	t_vec3	l_point;
	float	br_ratio;
	t_color	rgb;
}	t_light;

// ◦ Sphere: sp 0.0,0.0,20.6 12.6 10,0,255
// ∗ identifier: sp
// ∗ x,y,z coordinates of the sphere center: 0.0,0.0,20.6
// ∗ the sphere dmeter: 12.6
// ∗ R,G,B colors in range [0-255]: 10, 0, 255
typedef struct s_sphere
{
	t_vec3		sp_center;
	float		radius; // lin modify
	t_color		rgb;
}	t_sphere;

// ◦ Plane: pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
// ∗ identifier: pl
// ∗ x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
// ∗ 3d normalized vector. In range [-1,1]: 0.0,1.0,0.0
// ∗ R,G,B colors in range [0-255]: 0,0,225
typedef struct s_plane
{
	t_vec3		p_in_pl;
	t_vec3		nor_v;
	t_color		rgb;
}	t_plane;

// ◦ Cylinder: cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
// ∗ identifier: cy
// ∗ x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
// ∗ 3d normalized vector of axis of cylinder In range [-1,1]:0.0,0.0,1.0
// ∗ the cylinder diameter: 14.2
// ∗ the cylinder height: 21.42
// ∗ R,G,B colors in range [0,255]: 10, 0, 255
typedef struct s_cylinder
{
	t_vec3		cy_center;
	t_vec3		cy_axis;
	float		radius;
	float		height;
	t_color		rgb;
}	t_cylinder;

typedef enum s_obj_type
{
	OBJ_SP,
	OBJ_PL,
	OBJ_CY,
}	t_obj_type;

typedef struct s_object
{
	t_obj_type			type;
	void				*data;
	struct s_object		*next;
}	t_object;

// a scene with everything inside
typedef struct s_scene
{
	int			fd;
	int32_t		width;
	int32_t		height;
	t_a_light	ambient_light;
	t_camera	cam;
	t_light		light;
	bool		al_existence;
	bool		c_existence;
	bool		l_existence;
	t_object	*objects;
	mlx_t		*mlx;
	mlx_image_t	*img;
	bool		need_loop;
	bool		running;
	bool		line_error;
}	t_scene;

/* ~~~~~~~~~~~~~~~~~~ RENDERING STRUC ~~~~~~~~~~~~~~~~~~ */
//the width and height of the viewport
//forward, right, up define the orientation of the camera in 3D space:
//viewport_origin;top-left corner of the viewport (strat point)
//camera_origin; position of the camera
typedef struct s_camera_view
{
	float	viewport_width;
	float	viewport_height;
	t_vec3	viewport_origin;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	t_vec3	camera_origin;
	t_vec3	horizontal;
	t_vec3	vertical;
}	t_camera_view;

typedef struct s_hit_sphere_info
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	real_t;
	float	t1;
	float	t2;
}	t_hit_sphere_info;

typedef struct s_hit_cy_info
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	t;
	t_vec3	oc_prep;
	t_vec3	d_prep;
	float	projection;
	t_vec3	hit_vec;
	t_vec3	hit_point;
	t_vec3	projected;
}	t_hit_cy_info;

typedef struct s_hit_record
{
	float		t;
	t_vec3		point;
	t_vec3		normal;
	t_color		rgb;
	t_object	*obj;
}	t_hit_record;

typedef struct s_render_data
{
	t_ray			ray;
	t_camera_view	view;
	t_hit_record	rec;
	t_color			c;
}	t_render_data;

/* ~~~~~~~~~~~~~~~~~~ VECTOR ~~~~~~~~~~~~~~~~~~ */
//vector
t_vec3	vec_add(t_vec3 a, t_vec3 b);
t_vec3	vec_sub(t_vec3 a, t_vec3 b);
t_vec3	vec_scale(t_vec3 a, float scalar);
float	vec_len(t_vec3 a);
t_vec3	vec_normalize(t_vec3 v);
float	vec_dot(t_vec3 a, t_vec3 b);
t_vec3	vec_cross(t_vec3 a, t_vec3 b);

/* ~~~~~~~~~~~~~~~~~~ PARSING ~~~~~~~~~~~~~~~~~~ */
//parsing_file.c          4/5
t_scene	*parsing(int ac, char **av);
void	ft_free_scene(t_scene *scene);
//parsing_line.c	3/5		check each line, return true or false
bool	validating_parsing_line(char *line, t_scene *scene);
bool	add_obj_to_scene(t_scene *scene, t_obj_type type, void *data);
// parsing_env.c     3/5	a_light, camera, light:
bool	validate_parsing_tokens_a(char **tokens, t_scene *scene);
bool	validate_parsing_tokens_c(char **tokens, t_scene *scene);
bool	validate_parsing_tokens_l(char **tokens, t_scene *scene);
//parsing_obj_sp.c     3/5	sphere
bool	validate_parsing_tokens_sp(char **tokens, t_scene *scene);
//parsing_obj_2.c     5/5	plane and cylinder
bool	validate_parsing_tokens_pl(char **tokens, t_scene *scene);
bool	validate_parsing_tokens_cy(char **tokens, t_scene *scene);
//parsing_utils_1.c   3/5	str helpers
float	ft_atoi_float(char *str);
int		count_token_nbr(char **tokens);
void	free_three_arr(char **vec_1, char **vec_2, char **colors);
void	normalize_line(char *line);
//parsing_utils_2.c   5/5	fill **str to t_vec and t_color
bool	check_valid_float(char *str);
bool	do_color(char **colors, t_color *rgb);
bool	do_normalized_vectoy(char **vec, t_vec3 *vec_nor);
bool	do_xyz_vectoy(char **vec, t_vec3 *vec_xyz);

/* ~~~~~~~~~~~~~~~~~~ RAY_tracing ~~~~~~~~~~~~~~~~~~ */
//cemera_ray.c
t_vec3	vec3(float x, float y, float z);
void	init_camera_frame(t_camera	*cam, t_vec3 *right, t_vec3 *up);
void	init_viewport(t_scene *scene, t_camera_view *view);
t_ray	generate_primary_ray(int x, int y, t_camera_view *view, t_scene *scene);
//hit_sphere_plane
bool	hit_sphere(t_ray ray, t_sphere *sphere, t_hit_record *rec);
bool	hit_plane(t_ray ray, t_plane *plane, t_hit_record *rec);
//hit_cylinder
bool	hit_cylinder(t_ray ray, t_cylinder *cy, t_hit_record *rec);
//hit_cylinder_utils
bool	hit_bottom_cap(t_ray ray, t_cylinder *cy, t_hit_record *rec);
bool	hit_top_cap(t_ray ray, t_cylinder *cy, t_hit_record *rec);
//hit obejcts
bool	hit_objects(t_ray ray, t_object *obj, t_hit_record *rec);
//handle_light_utils
int		clamp(int value, int min, int max);
t_color	apply_ambient(t_color obj_color, t_a_light amb);
t_color	apply_diffuse(t_color obj_color, t_light light, t_hit_record rec);
t_color	get_color_from_object(t_object *obj);
//handle_light
t_color	final_color(t_scene *scene, t_hit_record rec);
//handle_shadow
bool	is_in_shadow(t_hit_record rec, t_light light, t_object *obj);

/* ~~~~~~~~~~~~~~~~~~ MLX ~~~~~~~~~~~~~~~~~~ */
//mlx_window.c			4/5
bool	mlx_window(t_scene *scene);
// keyboard.c			5/5	close by clicking x and 3 types of keyboard controk
void	close_window(void *param);
void	key_hook(mlx_key_data_t keydata, void *param);
//update_scene.c		4/5
void	change_move(t_scene *scene, t_vec3 move);
void	change_scale(t_scene *scene, float scale);
void	change_rotation(t_scene *scene, t_vec3 y_axis, float angle);

#endif