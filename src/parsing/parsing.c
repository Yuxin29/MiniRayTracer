#include "miniRT.h"
#include "parsing.h"



//test printing delete alter
//=======================================================
static void print_a_light(t_a_light *a)
{
    if (!a)
    {
        printf("Ambient light is NULL\n");
        return;
    }
    printf("Ambient Light:\n");
    printf("  ratio: %.2f\n", a->ratio);
    printf("  color: R=%d G=%d B=%d\n", a->r, a->g, a->b);
}

static void print_camera(t_camera *c)
{
    if (!c)
    {
        printf("Camera is NULL\n");
        return;
    }
    printf("Camera:\n");
    printf("  position: x=%.2f y=%.2f z=%.2f\n", c->v_point.x, c->v_point.y, c->v_point.z);
    printf("  orientation: x=%.2f y=%.2f z=%.2f\n", c->v_orien.x, c->v_orien.y, c->v_orien.z);
    printf("  FOV: %d\n", c->fov);
}

static void print_sphere(t_sphere *s)
{
    if (!s)
    {
        printf("Sphere is NULL\n");
        return;
    }
    printf("Sphere:\n");
    printf("  center: x=%.2f y=%.2f z=%.2f\n", s->sp_center.x, s->sp_center.y, s->sp_center.z);
    printf("  diameter: %.2f\n", s->dia);
    printf("  color: R=%d G=%d B=%d\n", s->r, s->g, s->b);
}
//=======================================================

//check if each line is valid,
//it has to start with the 6 identifies, it can be empty line
//return 0 as error and 1 as valid line
static int validating_identifier(char *line)
{
	int len;
	
	// printf("%s", "debug");
	// if (!line)
	// 	return 0;
	len = ft_strlen(line);
	if (*line && ft_isspace(*line))
		return (1);
	if (len >= 2 && ft_strncmp(line, "A ", 2) == 0)
		return (1);
	if (len >= 2 && ft_strncmp(line, "C ", 2) == 0)
		return (1);
	if (len >= 2 && ft_strncmp(line, "L ", 2) == 0)
		return (1);
	if (len >= 3 && ft_strncmp(line, "sp ", 3) == 0)
		return (1);
	if (len >= 3 && ft_strncmp(line, "pl ", 3) == 0)
		return (1);
	if (len >= 3 && ft_strncmp(line, "cy ", 3) == 0)
		return (1);
	return (0);
}


void parsing_line(char *line, t_scene *scene)
{
	if (*line && ft_isspace(line[0]))
		line++ ;
	if (!*line || *line == '\n')
		return ;

	if (ft_strncmp(line, "A ", 2) == 0)
	{
		printf("%s", "parse a light");
		get_a_light(line, scene);
	}
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		printf("%s", "parse a camera");
		get_camera(line, scene);
	}
	// else if (ft_strncmp(line, "L ", 2) == 0)
	// 	get_light(line, scene);
	if (ft_strncmp(line, "sp ", 3) == 0)
	{
		printf("%s", "parse a sphere");
		get_sphere(line, scene);
	}
	// else if (line[0] == 'p' && line[1] == 'l')
		// 	get_plane(line, scene);
	// else if (line[0] == 'c' && line[1] == 'y')
		// 	get_cylinder(line, scene);
}

static int	precheck_av(int ac, char **av, t_scene *scene)
{
	char	*ext;

	if (ac != 2)
		return(err_msg_code("wrong ac nbr", 0));
	ext = ft_strrchr(av[1], '.');
	if (!ext || ft_strcmp(ext, ".rt") != 0)
		return (err_msg_code("wrong format", 0));
	scene->fd = open(av[1], O_RDONLY);
	if (scene->fd == -1)
		return (err_msg_code("open file failed", 0));
	return (1);
}

//return 0 as error and 1 as parsing success
int parsing(int ac, char **av, t_scene *scene)
{
	char	*line;
	
	if (!precheck_av(ac, av, scene))
		return (0);
	line = get_next_line(scene->fd);
	while (1)
	{
		line = get_next_line(scene->fd);
		if (!line)
			break ;
		printf("%s", line);	//test printing, remove later
		if (validating_identifier(line) == 0)
		{
			ft_putstr_fd("invalid line in the file", 1);
			free(line);
			ft_free_scene(scene);
			close(scene->fd);
			return (0);
		}
		if (line[0])
		 	parsing_line(line, scene);
		free (line);
	}

	//test print
	printf("\n\n%s\n", "test printing scene");
	if (scene->ambient_light)
		print_a_light(scene->ambient_light);
	if (scene->cam)
		print_camera(scene->cam);
	if (scene->sp)
		print_sphere(scene->sp);

	return (1);
}
