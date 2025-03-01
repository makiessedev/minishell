#include "minishell.h"

static void	storage_word_token(t_token **token_lst, char *str, int index, int start)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (index - start + 1));
	if (!word)
		return ;
	while (start < index)
	{
		word[i] = str[start];
		start++;
		i++;
	}
	word[i] = '\0';
	lst_add_back_token(token_lst, lst_new_token(word, ft_strdup(word), WORD_TOKEN, NORMAL_MODE));
	return ;
}

static void	storage_separator_token(t_token **token_lst, char *str, int index, int type)
{
	int		i;
	char	*sep;

	i = 0;
	if (type == APPEND_TOKEN || type == HEREDOC_TOKEN)
	{
		sep = malloc(sizeof(char) * 3);
		if (!sep)
			return ;
		while (i < 2)
			sep[i++] = str[index++];
		sep[i] = '\0';
		lst_add_back_token(token_lst, lst_new_token(sep, NULL, type, NORMAL_MODE));
	}
	else
	{
		sep = malloc(sizeof(char) * 2);
		if (!sep)
			return ;
		while (i < 1)
			sep[i++] = str[index++];
		sep[i] = '\0';
		lst_add_back_token(token_lst, lst_new_token(sep, NULL, type, NORMAL_MODE));
	}
	return ;
}

int	storage_word_or_separator_token(int *i, int start, t_main *main_data)
{
	int	type;

	type = get_type_separator_token(main_data->user_input, (*i));
	if (type)
	{
		if ((*i) != 0 && get_type_separator_token(main_data->user_input, (*i) - 1) == 0)
			storage_word_token(&main_data->token, main_data->user_input, (*i), start);
		if (type == APPEND_TOKEN || type == HEREDOC_TOKEN || type == PIPE_TOKEN
			|| type == INPUT_TOKEN || type == REDIRECT_TOKEN || type == END_TOKEN)
		{
			storage_separator_token(&main_data->token, main_data->user_input, (*i), type);
			if (type == APPEND_TOKEN || type == HEREDOC_TOKEN)
				(*i)++;
		}
		start = (*i) + 1;
	}
	return (start);
}

int	get_type_separator_token(char *str, int i)
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
