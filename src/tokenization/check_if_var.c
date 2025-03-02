#include "minishell.h"

static void	variable_check(t_token **token_node)
{
	int	i;

	i = 0;
	while ((*token_node)->token[i])
	{
		if ((*token_node)->token[i] == '$')
		{
			if ((*token_node)->prev && (*token_node)->prev->type == HEREDOC_TOKEN)
				break ;
			(*token_node)->type = VAR_TOKEN;
			return ;
		}
		i++;
	}
}

int	check_if_var(t_token **token_lst)
{
	t_token	*temp;

	temp = *token_lst;
	if (temp->type == PIPE_TOKEN)
	{
		throw_message_error("syntax error near unexpected token", temp->token, true);
		return (EXIT_FAILURE);
	}
	while (temp)
	{
		variable_check(&temp);
		if (check_consecutives(&temp) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
