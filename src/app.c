#include "minishell.h"

void	bootstrap(t_main *main_data)
{
	while (1)
	{
    set_signals_interactive();
		main_data->user_input = readline(PROMPT);
		if (parse_user_input(main_data) == true)
			g_last_exit_code = execute(main_data);
		else
			g_last_exit_code = 1;
		free_data(main_data, false);
	}
}