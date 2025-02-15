#include "minishell.h"

void	bootstrap(t_data *data)
{
	while (1)
	{
		data->user_input = readline(PROMPT);
		if (parse_user_input(data) == true)
			g_last_exit_code = execute(data);
		else
			g_last_exit_code = 1;
		free_data(data, false);
	}
}