#include "minishell.h"

void	parse_input_and_execute(t_minishell	*minisheel_data)
{
	if (parse(minisheel_data))
		minisheel_data->last_command_exit_code = execute(minisheel_data);
	else
		minisheel_data->last_command_exit_code = 1;
	return (true);
}

static bool parse(t_minishell	*minisheel_data)
{

}

static int	execute(t_minishell	*minisheel_data)
{

}
