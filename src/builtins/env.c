#include "minishell.h"

int	env_builtin(t_minishell *data, char **args)
{
	int	i;

	if (args && args[1])
		return (errmsg_cmd("env", NULL, "too many arguments", 2));
	i = 0;
	if (!data->envp)
		return (EXIT_FAILURE);
	while (data->envp[i])
		ft_putendl_fd(data->envp[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
