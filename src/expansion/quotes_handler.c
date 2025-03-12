#include "minishell.h"

int	calculate_length_without_quotes(char *str, int count, int i)
{
	int	status;

	status = NORMAL_MODE;
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
		else if ((str[i] == '\'' && status == SINGLE_QUOTE) || (str[i] == '\"' && status == DOUBLE_QUOTE))
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

bool	contains_quotes(char *str)
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

int	process_and_remove_quotes(t_main *main_data)
{
	t_token	*temp;

	temp = main_data->token;
	while (temp)
	{
		if (contains_quotes(temp->token) == true && (!temp->prev || (temp->prev && temp->prev->type != HEREDOC_TOKEN)))
			remove_quotes(&temp);
		temp = temp->next;
	}
	return (0);
}
