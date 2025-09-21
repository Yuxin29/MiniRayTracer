#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "miniRT.h"
# include "parsing.h"
# include <math.h>

typedef struct s_object t_object;
typedef struct s_sphere t_sphere;
typedef struct s_a_light t_a_light;
typedef struct s_light t_light;
typedef struct s_plane t_plane;
typedef struct s_color t_color;

//struct
//lin modify type, 8 bits for each color instead of using 32 bits(int) for each color
typedef struct s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_color;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;;
}	t_ray;

typedef struct s_hit_record
{
	float	t; //t represents how far along the ray we go to reach the hit point.
	t_vec3	point; //hit point
	t_vec3	normal; //A normal is a vector that points perpendicular to the surface at a specific point.
	t_color	rgb; //0916modify
}	t_hit_record;

typedef struct s_hit_info
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	t;
}	t_hit_info;

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

bool	hit_objects(t_ray ray, t_object *obj, t_hit_record *rec);

t_vec3	vec3(float x, float y, float z);
void	init_camera_frame(t_camera	*cam, t_vec3 *right, t_vec3 *up);

void	init_viewport(t_scene *scene, t_camera_view *view);
t_ray	generate_primary_ray(int x, int y, t_camera_view *view, t_scene *scene);

//hit_sphere_plane
bool	hit_sphere(t_ray ray, t_sphere *sphere, t_hit_record *rec);
bool	hit_plane(t_ray ray, t_plane *plane, t_hit_record *rec);
//handle_light
t_color	final_color(t_color obj_color, t_scene *scene, t_hit_record rec);
//handle_shadow
bool	is_in_shadow(t_hit_record rec, t_light light, t_object *obj);

#endif
