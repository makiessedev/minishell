#include "minishell.h"

static void unused_args(int ac, char **av)
{
	(void)ac;
	(void)av;
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	unused_args(ac, av);
	ft_memset(&data, 0, sizeof(t_data));
	if (!init_data(&data, env))
		exit_shell(NULL, EXIT_FAILURE);
	bootstrap(&data);
	exit_shell(&data, g_last_exit_code);
	return (0);
}
