#include "miniRT.h"

/**
 * @brief 	parsing one line according to the element type
 * @param 	tokens tokens of the line after split
 * @param 	*t_scene scene pointer to the scene struct
 * @return	bool true if line is valid and parsed, false otherwise
 *
 */
static bool	validate_tokens_content(char **tokens, t_scene *scene)
{
	if (ft_strncmp(tokens[0], "A", 1) == 0)
		return (validate_parsing_tokens_a(tokens, scene));
	if (ft_strncmp(tokens[0], "C", 1) == 0)
		return (validate_parsing_tokens_c(tokens, scene));
	if (ft_strncmp(tokens[0], "L", 1) == 0)
		return (validate_parsing_tokens_l(tokens, scene));
	if (ft_strncmp(tokens[0], "sp", 2) == 0)
		return (validate_parsing_tokens_sp(tokens, scene));
	if (ft_strncmp(tokens[0], "pl", 2) == 0)
		return (validate_parsing_tokens_pl(tokens, scene));
	if (ft_strncmp(tokens[0], "cy", 2) == 0)
		return (validate_parsing_tokens_cy(tokens, scene));
	return (false);
}

/**
 * @brief 	adding the parsed object to the scene's object list
 *
 * @param 	type type of the object to add
 * @param 	data pointer to the object data struct	
 * @param 	*t_scene scene pointer to the scene struct
 * @return	bool true if line is valid and parsed, false otherwise
 *
 */
bool	add_obj_to_scene(t_scene *scene, t_obj_type type, void *data)
{
	t_object	*obj;
	t_object	*tmp;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (false);
	obj->type = type;
	obj->data = data;
	obj->next = NULL;
	if (!scene->objects)
		scene->objects = obj;
	else
	{
		tmp = scene->objects;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = obj;
	}
	return (true);
}

/**
 * @brief 	parsing one line of the .rt file
 * @param 	line line to parse
 * @param 	*t_scene scene pointer to the scene struct
 * @return	bool true if line is valid and parsed, false otherwise
 *
 * @note normalize the line first, then split the line into tokens
 *       validate the tokens content according to the element type
 */
bool	validating_parsing_line(char *line, t_scene *scene)
{
	char	**tokens;
	int		i;

	i = 0;
	if (scene->line_error == true)
		return (false);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (true);
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
	{
		free_three_arr(tokens, NULL, NULL);
		return (false);
	}
	if (!validate_tokens_content(tokens, scene))
	{
		ft_free_arr(tokens);
		return (false);
	}
	ft_free_arr(tokens);
	return (true);
}
