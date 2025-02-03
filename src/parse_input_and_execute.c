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

void save_word_token(t_minishell minishell_data, int i, int user_input_start)
{


}

void save_separator_token()
{

}

int get_separator_token(t_minishell *minishell_data, int i)
{
	char *input_user;
	int token;
	
	input_user = minishell_data->input_user 
	if ((input_user[i] >= 9 && input_user[i] <= 13) || input_user[i] == 32)
		token = SPACE_TOKEN;
	else if (input_user[i] == '|')
		token = PIPE_TOKEN;
	else if (input_user[i] == '<' && input_user[i+1] == '<')
		token = HEREDOC_TOKEN;
	else if (input_user[i] == '>' && input_user[i+1] == '>')
		token = APPEND_TOKEN;
	else if (input_user[i] == '<')
		token = INPUT_TOKEN;
	else if (input_user[i] == '>')
		token = REDIRECT_TOKEN;
	else if (input_user[i] == '\0')
		token = END_TOKEN;
	else
		return (false)
	return (token);
}

int save_token(t_minishell *minisheel_data, int user_input_start, int *i)
{
	int token_type;

	token_type = get_separator_token(minisheel_data, *i);
	if (token_type)
	{
		if (*i != 0 && get_separator_token(minisheel_data, *i - 1) == false)
			save_word_token(minisheel_data, *i, user_input_start);
		if (
			token_type == PIPE_TOKEN || token_type == REDIRECT_TOKEN || 
			token_type == INPUT_TOKEN || token_type == APPEND_TOKEN ||
			token_type == HEREDOC_TOKEN || token_type == END_TOKEN 
		)
		{
			save_separator_token();
			if (token_type == APPEND_TOKEN || token_type == HEREDOC_TOKEN)
				(*i)++;
		}
		user_input_start = (*i) + 1;
	}
	return (user_input_start);
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
		if (minisheel_data->input_user[i] == ' ' && user_input_status_quote == NORMAL_MODE)
			user_input_start = save_token(minisheel_data, user_input_start, &i)
		
	}
	if (user_input_status_quote != NORMAL_MODE)
		return (ft_putstr_fd("minishell: unexpected unclose quotes \"'\" or '\"'"), false)
	return (true)
}

static int	execute(t_minishell	*minisheel_data)
{

}
