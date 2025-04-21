/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:55:38 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 22:00:15 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arguments(t_token *temp)
{
	int	i;

	i = 0;
	while (temp && (temp->type == WORD_TOKEN || temp->type == VAR_TOKEN))
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	remove_empty_variable_arguments(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	while (temp->type == WORD_TOKEN || temp->type == VAR_TOKEN)
	{
		if (temp->type == VAR_TOKEN && temp->token[0] == '\0'
			&& temp->var_exists == FALSE)
		{
			temp = temp->next;
			if (temp == (*tokens)->next)
				(*tokens) = (*tokens)->next;
			lstdelone_token(temp->prev, erase_pointer);
		}
		else
			temp = temp->next;
	}
}
