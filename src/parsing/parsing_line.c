#include "miniRT.h"
#include "parsing.h"

//parsing one line
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

//check if each line is valid,
//it has to start with the 6 identifies, it can be empty line
//return 0 as error and 1 as valid line
//the line could be empty line
static bool	validating_line_id_and_nbr(char **tokens)
{
	int	nbr;

	if (!tokens || !tokens[0])
		return (false);
	nbr = count_token_nbr(tokens);
	if (ft_strcmp(tokens[0], "A") == 0 && nbr == 3)
		return (true);
	if (ft_strcmp(tokens[0], "C") == 0 && nbr == 4)
		return (true);
	if (ft_strcmp(tokens[0], "L") == 0 && nbr == 3)
		return (true);
	if (ft_strcmp(tokens[0], "sp") == 0 && nbr == 4)
		return (true);
	if (ft_strcmp(tokens[0], "pl") == 0 && nbr == 4)
		return (true);
	if (ft_strcmp(tokens[0], "cy") == 0 && nbr == 6)
		return (true);
	return (false);
}


bool	validating_parsing_line(char *line, t_scene *scene)
{
	char	**tokens;

	if (!line[0])
		return (true);
	tokens = ft_split(line, ' ');
	if (!validating_line_id_and_nbr(tokens))
	{
		ft_free_arr(tokens);
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
