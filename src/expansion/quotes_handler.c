#include "minishell.h"

int	count_len(char *str, int count, int i)
{
	int	status;

	status = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && status == NORMAL_MODE)
		{
			if (str[i] == '\'')
				status = SINGLE_QUOTE;
			if (str[i] == '\"')
				status = DOUBLE_QUOTE;
			i++;
			continue ;
		}
		else if ((str[i] == '\'' && status == SINGLE_QUOTE)
			|| (str[i] == '\"' && status == DOUBLE_QUOTE))
		{
			status = NORMAL_MODE;
			i++;
			continue ;
		}
		count++;
		i++;
	}
	return (count + 1);
}

bool	quotes_in_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

int	handle_quotes(t_data *data)
{
	t_token	*temp;

	temp = data->token;
	while (temp)
	{
		if (quotes_in_string(temp->str) == true
			&& (!temp->prev || (temp->prev && temp->prev->type != HEREDOC_TOKEN)))
			remove_quotes(&temp);
		temp = temp->next;
	}
	return (0);
}
