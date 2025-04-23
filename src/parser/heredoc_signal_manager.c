#include "minishell.h"

static void	update_prompt(int signo)
{
	(void)signo;
    exit(0);
}

static void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &act, NULL);
}

void	heredoc_signal_manager(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &update_prompt;
	sigaction(SIGINT, &act, NULL);
}