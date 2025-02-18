#include "minishell.h"

static void unused_args(int ac, char **av)
{
	(void)ac;
	(void)av;
}

int	main(int ac, char **av, char **env)
{
	t_main	main_data;

	unused_args(ac, av);
	ft_memset(&main_data, 0, sizeof(t_main));
	if (!init_data(&main_data, env))
		exit_shell(NULL, EXIT_FAILURE);
	bootstrap(&main_data);
	exit_shell(&main_data, g_last_exit_code);
	return (0);
}
