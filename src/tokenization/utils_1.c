#include "minishell.h"

int	check_status_quote(int status, char *str, int i)
{
	if (str[i] == '\'' && status == NORMAL_MODE)
		status = SINGLE_QUOTE;
	else if (str[i] == '\"' && status == NORMAL_MODE)
		status = DOUBLE_QUOTE;
	else if (str[i] == '\'' && status == SINGLE_QUOTE)
		status = NORMAL_MODE;
	else if (str[i] == '\"' && status == DOUBLE_QUOTE)
		status = NORMAL_MODE;
	return (status);
}

int	storage_word_or_separator_token(int *i, char *str, int start, t_main *main_data)
{
	int	type;

	type = is_separator(str, (*i));
	if (type)
	{
		if ((*i) != 0 && is_separator(str, (*i) - 1) == 0)
			storage_word_token(&main_data->token, str, (*i), start);
		if (type == APPEND_TOKEN || type == HEREDOC_TOKEN || type == PIPE_TOKEN
			|| type == INPUT_TOKEN || type == REDIRECT_TOKEN || type == END_TOKEN)
		{
			storage_separator_token(&main_data->token, str, (*i), type);
			if (type == APPEND_TOKEN || type == HEREDOC_TOKEN)
				(*i)++;
		}
		start = (*i) + 1;
	}
	return (start);
}

int	storage_separator_token(t_token **token_lst, char *str, int index, int type)
{
	int		i;
	char	*sep;

	i = 0;
	if (type == APPEND_TOKEN || type == HEREDOC_TOKEN)
	{
		sep = malloc(sizeof(char) * 3);
		if (!sep)
			return (1);
		while (i < 2)
			sep[i++] = str[index++];
		sep[i] = '\0';
		lst_add_back_token(token_lst, lst_new_token(sep, NULL, type, NORMAL_MODE));
	}
	else
	{
		sep = malloc(sizeof(char) * 2);
		if (!sep)
			return (1);
		while (i < 1)
			sep[i++] = str[index++];
		sep[i] = '\0';
		lst_add_back_token(token_lst, lst_new_token(sep, NULL, type, NORMAL_MODE));
	}
	return (0);
}

int	storage_word_token(t_token **token_lst, char *str, int index, int start)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (index - start + 1));
	if (!word)
		return (1);
	while (start < index)
	{
		word[i] = str[start];
		start++;
		i++;
	}
	word[i] = '\0';
	lst_add_back_token(token_lst, \
			lst_new_token(word, ft_strdup(word), WORD_TOKEN, NORMAL_MODE));
	return (0);
}

int	is_separator(char *str, int i)
{
	if (((str[i] > 8 && str[i] < 14) || str[i] == 32))
		return (SPACES_TOKEN);
	else if (str[i] == '|')
		return (PIPE_TOKEN);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC_TOKEN);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND_TOKEN);
	else if (str[i] == '<')
		return (INPUT_TOKEN);
	else if (str[i] == '>')
		return (REDIRECT_TOKEN);
	else if (str[i] == '\0')
		return (END_TOKEN);
	else
		return (0);
}
