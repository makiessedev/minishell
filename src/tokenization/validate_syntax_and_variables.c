/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax_and_variables.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:57:02 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 22:05:26 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	detect_variable(t_token **token_node)
{
	int	i;

	i = 0;
	while ((*token_node)->token[i])
	{
		if ((*token_node)->token[i] == '$')
		{
			if ((*token_node)->prev
				&& (*token_node)->prev->type == HEREDOC_TOKEN)
				break ;
			(*token_node)->type = VAR_TOKEN;
			return ;
		}
		i++;
	}
}

static int	has_consecutive_operators(t_token *token_node)
{
	if (token_node->prev)
	{
		if (token_node->type == PIPE_TOKEN
			&& token_node->prev->type == PIPE_TOKEN)
			return (TRUE);
		if (token_node->type > PIPE_TOKEN
			&& token_node->prev->type > PIPE_TOKEN)
			return (TRUE);
		if (token_node->type == END_TOKEN
			&& token_node->prev->type >= PIPE_TOKEN)
			return (TRUE);
	}
	return (FALSE);
}

static int	validate_operator_sequence(t_token **token_lst)
{
	t_token	*temp;

	temp = *token_lst;
	while (temp)
	{
		if (has_consecutive_operators(temp) == TRUE)
		{
			if (temp->type == END_TOKEN && temp->prev
				&& temp->prev->type > PIPE_TOKEN)
				throw_message_error("syntax error near unexpected token",
					"newline", TRUE);
			else if (temp->type == END_TOKEN && temp->prev)
				throw_message_error("syntax error near unexpected token",
					temp->prev->token, TRUE);
			else
				throw_message_error("syntax error near unexpected token",
					temp->token, TRUE);
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
		throw_message_error("syntax error near unexpected token", temp->token,
			TRUE);
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
