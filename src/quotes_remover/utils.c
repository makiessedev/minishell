/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:56:17 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 20:24:20 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		else if ((str[i] == '\'' && status == SINGLE_QUOTE) || (str[i] == '\"'
				&& status == DOUBLE_QUOTE))
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

void	set_quote_mode(t_token **token_node, int *i)
{
	if ((*token_node)->token[*i] == '\'')
		(*token_node)->status = SINGLE_QUOTE;
	if ((*token_node)->token[*i] == '\"')
		(*token_node)->status = DOUBLE_QUOTE;
	(*i)++;
}

bool	is_quotes_and_normal_mode(t_token **token_node, int i)
{
	if (((*token_node)->token[i] == '\'' || (*token_node)->token[i] == '\"')
			&& (*token_node)->status == NORMAL_MODE)
		return (true);
	else
		return (false);
}

bool	reset_to_normal_mode(t_token **token_node, int *i)
{
	if (((*token_node)->token[*i] == '\''
			&& (*token_node)->status == SINGLE_QUOTE)
			|| ((*token_node)->token[*i] == '\"'
			&& (*token_node)->status == DOUBLE_QUOTE))
	{
		(*token_node)->status = NORMAL_MODE;
		(*i)++;
		return (true);
	}
	else
		return (false);
}
