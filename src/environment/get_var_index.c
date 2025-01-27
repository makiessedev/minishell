#include "minishell.h"

int get_var_index(char *var, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
			return (i);
		i++;
	}
	return (-1);
}