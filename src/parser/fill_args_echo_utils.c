#include "minishell.h"

char	*join_vars(t_token **token_node)
{
	t_token	*temp;
	char	*str;

	temp = *token_node;
	str = ft_strdup(temp->token);
	while (temp->type == VAR_TOKEN && temp->next->type == VAR_TOKEN
		&& temp->next->join == true)
	{
		str = ft_strjoin(str, temp->next->token);
		temp = temp->next;
	}
	*token_node = temp;
	return (str);
}

int	count_args(t_token *temp)
{
	int	i;

	i = 0;
	while (temp && (temp->type == WORD_TOKEN || temp->type == VAR_TOKEN))
	{
		if (temp->type == VAR_TOKEN && temp->join == true)
		{
			while (temp->type == VAR_TOKEN && temp->join == true)
				temp = temp->next;
			i++;
		}
		else
		{
			i++;
			temp = temp->next;
		}
	}
	return (i);
}

char	**copy_in_new_tab(int len, char **new_tab,
			t_command *last_cmd, t_token *tmp)
{
	int	i;

	i = 0;
	while (i < len)
	{
		new_tab[i] = last_cmd->args[i];
		i++;
	}
	while (tmp->type == WORD_TOKEN || tmp->type == VAR_TOKEN)
	{
		if (tmp->join == true)
			new_tab[i] = join_vars(&tmp);
		else
			new_tab[i] = ft_strdup(tmp->token);
		i++;
		tmp = tmp->next;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

void	remove_empty_var_args(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	while (temp->type == WORD_TOKEN || temp->type == VAR_TOKEN)
	{
		if (temp->type == VAR_TOKEN && temp->token[0] == '\0'
			&& temp->var_exists == false)
		{
			temp = temp->next;
			if (temp == (*tokens)->next)
				(*tokens) = (*tokens)->next;
			lstdelone_token(temp->prev, free_ptr);
		}
		else
			temp = temp->next;
	}
}
