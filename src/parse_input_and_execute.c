#include "minishell.h"

void	parse_input_and_execute(t_minishell	*minisheel_data)
{
	if (parse(minisheel_data))
		minisheel_data->last_command_exit_code = execute(minisheel_data);
	else
		minisheel_data->last_command_exit_code = 1;
}

int set_status_quote(t_minishell *minisheel_data, int i)
{
	int user_input_status_quote;
	if (minisheel_data->input_user[i] == '"')
	{
		if (user_input_status_quote == NORMAL_MODE)
			user_input_status_quote = DOUBLE_QUOTE;
		else if (user_input_status_quote == DOUBLE_QUOTE)
			user_input_status_quote = NORMAL_MODE;
	}
	else if (minisheel_data->input_user[i] == '\'')
	{
		if (user_input_status_quote == NORMAL_MODE)
			user_input_status_quote = SINGLE_QUOTE;
		else if (user_input_status_quote == SINGLE_QUOTE)
			user_input_status_quote = NORMAL_MODE;
	}
	return (user_input_status_quote);
}

static bool parse(t_minishell	*minisheel_data)
{
	int i;
	int user_input_len;
	int user_input_start;
	int user_input_status_quote;

	i = -1;
	user_input_start = 0;
	user_input_len = ft_strlen(minisheel_data->input_user);
	user_input_status_quote = NORMAL_MODE;
	while (++i <= user_input_len)
	{
		user_input_status_quote = set_status_quote(minisheel_data)
		if (minisheel_data->input_user[i] == ' ' && status == NORMAL_MODE)
		{
			
		}
	}
	if (user_input_status_quote != NORMAL_MODE)
		return (ft_putstr_fd("minishell: unexpected unclose quotes \"'\" or '\"'"), false)
}

static int	execute(t_minishell	*minisheel_data)
{

}
