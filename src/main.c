#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (!start_check(&data, ac, av) || !init_data(&data, env))
		exit_shell(NULL, EXIT_FAILURE);
	bootstrap(&data);
	exit_shell(&data, g_last_exit_code);
	return (0);
}
