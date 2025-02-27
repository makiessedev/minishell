#include "minishell.h"

int	env_builtin(t_main *main_data, char **args)
{
	int	i;

	if (args && args[1])
		return (throw_command_error("env", NULL, "too many arguments", 2));
	i = 0;
	if (!main_data->env)
		return (EXIT_FAILURE);
	while (main_data->env[i])
		ft_putendl_fd(main_data->env[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
