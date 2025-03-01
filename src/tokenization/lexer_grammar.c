#include "minishell.h"

static bool	consecutive_ops(t_token *token_node)
{
	if (token_node->prev)
	{
		if (token_node->type == PIPE_TOKEN && token_node->prev->type == PIPE_TOKEN)
			return (true);
		if (token_node->type > PIPE_TOKEN && token_node->prev->type > PIPE_TOKEN)
			return (true);
		if (token_node->type == END_TOKEN && token_node->prev->type >= PIPE_TOKEN)
			return (true);
	}
	return (false);
}

int	check_consecutives(t_token **token_lst)
{
	t_token	*temp;

	temp = *token_lst;
	while (temp)
	{
		if (consecutive_ops(temp) == true)
		{
			if (temp->type == END_TOKEN && temp->prev && temp->prev->type > PIPE_TOKEN)
				throw_message_error("syntax error near unexpected token", "newline", true);
			else if (temp->type == END_TOKEN && temp->prev)
				throw_message_error("syntax error near unexpected token",
					temp->prev->token, true);
			else
				throw_message_error("syntax error near unexpected token", temp->token, true);
			return (EXIT_FAILURE);
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
