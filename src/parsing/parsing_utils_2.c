#include "miniRT.h"
#include "parsing.h"

static bool check_valid_color(char *color)
{
    int i;

    i = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]))
			return false;
		i++;
	}
	if (ft_atoi(color) > 255)
		return false;
	return true;
}

bool check_rgb(char **colors)
{
    int i;

    i = 0;
    if (count_token_nbr(colors) != 3)
		return false;
	while(colors[i])
	{
        if (!check_valid_color(colors[i]))
			return false;
		i++;
	}
	return true;
}

void do_color(char **colors, t_color *rgb)
{
	rgb->r = ft_atoi(colors[0]);
	rgb->g  = ft_atoi(colors[1]);
	rgb->b  = ft_atoi(colors[2]);
}