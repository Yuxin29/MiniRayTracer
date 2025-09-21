#include "miniRT.h"
#include "raytrace.h"

t_vec3	vec3(float x, float y, float z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}
/*
get the forward, up, right vector of the camera
forward → where the camera is looking (like Z axis)
right → the direction to the camera’s right-hand side (like X axis)
up → the direction above the camera’s head (like Y axis)
These three must form a right-handed system (not left-handed).
world_up: is a common convention in 3D graphics.
we should Prevent forward and world_up from being parallel
*/
void	init_camera_frame(t_camera	*cam, t_vec3 *right, t_vec3 *up)
{
	t_vec3	forward;
	t_vec3	world_up;

	forward = vec_normalize(cam->v_orien);
	world_up = vec3(0, 1, 0);
	if (fabs(vec_dot(forward, world_up)) > 0.999)
		world_up = vec3(0, 0, 1);
	*right = vec_normalize(vec_cross(world_up, forward));
	*up = vec_normalize(vec_cross(forward, *right));
}

//The viewport is a 2D virtual plane in front of the camera, through which rays are cast into the 3D world
//from camera → through a point on the viewport → into the 3D world
//The viewport helps define where each ray should go based on the pixel
//we assume the viewport is 1 unit in front of the camera
//we should convert the camera's field of view (FOV) from degrees to radians
//because in C, tan(), sin(), cos() expect the angle to be in radians, not degrees
/*Then the definitions are:
sin(θ) = Opposite / Hypotenuse
cos(θ) = Adjacent / Hypotenuse
tan(θ) = Opposite / Adjacent

center = cam->position + forward * 1.0
viewport_origin = center
	+ up * (viewport_height / 2)//move up
	- right * (viewport_width / 2)//move left
*/
void	init_viewport(t_scene *scene, t_camera_view *view)
{
	float	aspect_ratio;
	float	fov_rad;
	t_vec3	center;

	aspect_ratio = (float) scene->width / scene->height;
	fov_rad = scene->cam.fov * M_PI / 180.0f;
	view->viewport_height = 2 * tan(fov_rad / 2.0f);
	view->viewport_width = view->viewport_height * aspect_ratio;
	view->camera_origin = scene->cam.v_point;
	view->forward = vec_normalize(scene->cam.v_orien);
	init_camera_frame(&scene->cam, &view->right, &view->up);
	center = vec_add(view->camera_origin, vec_scale(view->forward, 1.0f));
	view->viewport_origin = center;
	view->viewport_origin = vec_add(view->viewport_origin, vec_scale(view->up, view->viewport_height / 2.0f));
	view->viewport_origin = vec_sub(view->viewport_origin, vec_scale(view->right, view->viewport_width / 2.0f));
}

/*
Each pixel corresponds to a point on the viewport.
u,v: Pixel index → percentage across the screen
because we can't shoot rays just using (x, y) — because that's only 2D
For each pixel (x, y):
Creates a ray from the camera, through the corresponding point on the viewport
Sends the ray into the 3D scene
Sees what it hits
Calculates the color (based on lighting, materials, etc.)
Writes the color to the pixel
*/
t_ray	generate_primary_ray(int x, int y, t_camera_view *view, t_scene *scene)
{
	float	u;
	float	v;
	t_vec3	pixel_pos;
	t_ray	ray;

	u = ((float)x + 0.5f) / (scene->width - 1);
	v = ((float)y + 0.5f) / (scene->height - 1);
	pixel_pos = vec_add(view->viewport_origin, vec_scale(view->right, u * view->viewport_width));
	pixel_pos = vec_sub(pixel_pos, vec_scale(view->up, v * view->viewport_height));
	ray.origin = view->camera_origin;
	ray.direction = vec_normalize(vec_sub(pixel_pos, ray.origin));
	return (ray);
}
