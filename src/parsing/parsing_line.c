#include "miniRT.h"
#include "parsing.h"

//parsing one line
static bool	validate_tokens(char **tokens, t_scene *scene)
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
static bool	validate_tokens_nbr(char **tokens)
{
	int	nbr;

	nbr = count_token_nbr(tokens);
	if (ft_strncmp(tokens[0], "A", 1) == 0 && nbr == 3)
		return (true);
	if (ft_strncmp(tokens[0], "C", 1) == 0 && nbr == 4)
		return (true);
	if (ft_strncmp(tokens[0], "L", 1) == 0 && nbr == 3)
		return (true);
	if (ft_strncmp(tokens[0], "sp", 2) == 0 && nbr == 4)
		return (true);
	if (ft_strncmp(tokens[0], "pl", 2) == 0 && nbr == 4)
		return (true);
	if (ft_strncmp(tokens[0], "cy", 2) == 0 && nbr == 6)
		return (true);
	return (false);
}

static bool	validating_line_id(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (*line && ft_isspace(*line)) //the line could be empty line
		return (true);
	if (len >= 2 && ft_strncmp(line, "A ", 2) == 0)
		return (true);
	if (len >= 2 && ft_strncmp(line, "C ", 2) == 0)
		return (true);
	if (len >= 2 && ft_strncmp(line, "L ", 2) == 0)
		return (true);
	if (len >= 3 && ft_strncmp(line, "sp ", 3) == 0)
		return (true);
	if (len >= 3 && ft_strncmp(line, "pl ", 3) == 0)
		return (true);
	if (len >= 3 && ft_strncmp(line, "cy ", 3) == 0)
		return (true);
	return (false);
}

bool	validating_parsing_line(char *line, t_scene *scene)
{
	char	**tokens;

	if (!validating_line_id(line))
		return (false);
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (false);
	if (!tokens[0] || !tokens[0][0])
	{
		ft_free_arr(tokens);
		return (false);
	}
	if (!validate_tokens_nbr(tokens))
	{
		ft_free_arr(tokens);
		return (false);
	}
	if (!validate_tokens(tokens, scene))
	{
		ft_free_arr(tokens);
		return (false);
	}
	ft_free_arr(tokens);
	return (true);
}
