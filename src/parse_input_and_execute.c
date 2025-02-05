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

void save_word_token(t_token **lst_token, t_minishell *data, int index, int user_input_start)
{
	int		i;
	char	*str;
	t_token *token;

	i = 0;
	str = malloc(sizeof(char) * (index - user_input_start + 1));
	if (!str)
		return (1);
	while (user_input_start < index)
	{
		str[i] = str[user_input_start];
		user_input_start++;
		i++;
	}
	str[i] = '\0';
	token = new_token(str, ft_strdup(token), WORD_TOKEN, NORMAL_MODE);
	add_token(lst_token, token);
	return (0);
}

void save_separator_token(t_token **lst_token, t_minishell *data, int index, int token_type)
{
	int		i;
	char	*token;
	int		token_length;

	i = 0;
	if (token_type == APPEND_TOKEN || token_type == HEREDOC_TOKEN)
		token_length = 2;
	else
		token_length = 1;
	token = malloc(sizeof(char) * (token_length + 1));
	if (!token)
		return (1);
	while (i < token_length)
		token[i++] = str[index++];
	token[i] = '\0';
	lst_add_back_token(lst_token, lst_new_token(token, NULL, token_type, NORMAL_MODE));
	return (0);
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
			save_word_token(&minisheel_data->token, minisheel_data, *i, user_input_start);
		if (
			token_type == PIPE_TOKEN || token_type == REDIRECT_TOKEN || 
			token_type == INPUT_TOKEN || token_type == APPEND_TOKEN ||
			token_type == HEREDOC_TOKEN || token_type == END_TOKEN 
		)
		{
			save_separator_token(&minisheel_data->token, minisheel_data, *i, token_type);
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
