#include "minishell.h"

static bool	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (true);
	return (false);
}

bool	is_only_space(char *str)
{
	int	index;

	index = -1;
	while (str[++index])
	{
		if (!ft_isspace(str[index]))
			return (false);
	}
	return (true);
}