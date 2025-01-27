#include "minishell.h"

char *get_var_value(char *var, char **envp)
{
	int	index;
	char	*value;

	index = get_var_index(var, envp);
	if (index == -1)
		return (NULL);
	value = ft_strchr(envp[index], '=') + 1;
	return (value);
}