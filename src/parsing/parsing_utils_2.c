#include "miniRT.h"

// a valid color string shoud be a pure digit from 0 - 255
static bool	check_valid_color(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]))
			return (false);
		if (i > 3)
			return (false);
		i++;
	}
	if (ft_atoi(color) > 255)
		return (false);
	return (true);
}

// a valid colors strs should be 3 strings
// each string needs to be a valid color (0 - 255)
bool	do_color(char **colors, t_color *rgb)
{
	int	i;

	i = 0;
	if (!colors)
		return (false);
	if (count_token_nbr(colors) != 3)
		return (false);
	while (colors[i])
	{
		if (!check_valid_color(colors[i]))
			return (false);
		i++;
	}
	rgb->r = ft_atoi(colors[0]);
	rgb->g = ft_atoi(colors[1]);
	rgb->b = ft_atoi(colors[2]);
	return (true);
}

// a valid float str must has a digit before .
//must has one and only one dote
//after the dote, the has to be at list one digit
bool	check_valid_float(char *str)
{
	int		i;

	i = 0;
	if (!str[0])
		return (false);
	if (str[i] == '-')
		i++;
	if (!ft_isdigit(str[i]))
		return (false);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '.')
	{
		i++;
		if (!str[i])
			return (false);
		if (!ft_isdigit(str[i]))
			return (false);
		while (ft_isdigit(str[i]))
			i++;
	}
	if (str[i] != '\0')
		return (false);
	return (true);
}

// x, y, z recommended Range : `-1000 ~ +1000`
// Enough space to place multiple objects and move the camera around
bool	do_xyz_vectoy(char **vec, t_vec3 *vec_xyz)
{
	int	i;

	i = 0;
	if (!vec)
		return (false);
	if (count_token_nbr(vec) != 3)
		return (false);
	while (vec[i])
	{
		if (!check_valid_float(vec[i]))
			return (false);
		if (ft_atoi_float(vec[i]) > 1000
			|| ft_atoi_float(vec[i]) < -1000)
			return (false);
		i++;
	}
	vec_xyz->x = ft_atoi_float(vec[0]);
	vec_xyz->y = ft_atoi_float(vec[1]);
	vec_xyz->z = ft_atoi_float(vec[2]);
	return (true);
}

// Each type of element can be separated by one or more line break(s).
// -> it coulld the empty space or self_defined
// 3d normalized orientation vector.
// In range [-1,1] for each x,y,z axis
bool	do_normalized_vectoy(char **vec, t_vec3 *vec_nor) //should modify?
{
	int	i;

	i = 0;
	if (!vec)
		return (false);
	if (count_token_nbr(vec) != 3)
		return (false);
	while (vec[i])
	{
		if (!check_valid_float(vec[i]))
			return (false);
		if (ft_atoi_float(vec[i]) > 1 || ft_atoi_float(vec[i]) < -1)
			return (false);
		i++;
	}
	vec_nor->x = ft_atoi_float(vec[0]);
	vec_nor->y = ft_atoi_float(vec[1]);
	vec_nor->z = ft_atoi_float(vec[2]);
	if (fabs(vec_len(*vec_nor)) < EPSILON)
		return (false);
	*vec_nor = vec_normalize(*vec_nor);
	return (true);
}
