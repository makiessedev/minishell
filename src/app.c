#include "minishell.h"

static void	update_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

void	signals_manager(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &update_prompt;
	sigaction(SIGINT, &act, NULL);
}

void	bootstrap(t_main *main_data)
{
	while (1)
	{
    signals_manager();
		main_data->user_input = readline(PROMPT);
		if (main_data->user_input == NULL)
			exit_builtin(main_data, NULL);
		if (parse_user_input(main_data) == true)
			g_exit_code = execute(main_data);
		else
			g_exit_code = 1;
		erase_main_data(main_data, false);
	}
}