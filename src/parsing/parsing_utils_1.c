#include "miniRT.h"

/**
 * @brief 	free three double strings safely
 *
 * @param 	vec_1 first double str array
 * @param 	vec_2 second double str array
 * @param 	colors third double str array
 */
void	free_three_arr(char **vec_1, char **vec_2, char **colors)
{
	if (vec_1)
		ft_free_arr(vec_1);
	if (vec_2)
		ft_free_arr(vec_2);
	if (colors)
		ft_free_arr(colors);
}

/**
 * @brief 	count number of tokens in a double string array
 *
 * @param 	tokens double str array
 * @return 	int number of tokens in the array
 */
int	count_token_nbr(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

/**
 * @brief 	get the decimal part of a float number
 */
static float	get_decimal(char *str, double number)
{
	float	decimal;
	float	fraction;

	str++;
	decimal = 1.0;
	fraction = 0.0;
	while (*str && ft_isdigit(*str))
	{
		fraction = fraction * 10 + (*str - '0');
		decimal *= 10.0;
		str++;
	}
	number += fraction / decimal;
	return (number);
}

/**
 * @brief 	normalize one line of the .rt file: change all spaces to the ' '
 *
 * @param 	line line to be normalized
 */
float	ft_atoi_float(char *str)
{
	float	sign;
	float	number;

	sign = 1.0;
	number = 0.0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1.0;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		number = number * 10 + (*str - '0');
		str++;
	}
	if (*str == '.')
		number = get_decimal((char *)str, number);
	return (number * sign);
}

/**
 * @brief 	normalize one line of the .rt file: change all spaces to the ' '
 *
 * @param 	line line to be normalized
 */
void	normalize_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			line[i] = ' ';
		i++;
	}
	return ;
}
