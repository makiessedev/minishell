#include "minishell.h"

static void	detect_variable(t_token **token_node)
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

static bool	has_consecutive_operators(t_token *token_node)
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

static int	validate_operator_sequence(t_token **token_lst)
{
	t_token	*temp;

	temp = *token_lst;
	while (temp)
	{
		if (has_consecutive_operators(temp) == true)
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


int	validate_syntax_and_variables(t_token **token_lst)
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
		detect_variable(&temp);
		if (validate_operator_sequence(&temp) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
