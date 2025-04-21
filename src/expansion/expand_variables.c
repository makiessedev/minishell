/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:54:56 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 20:22:43 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	should_expand_var(t_token *temp, int i)
{
	return (temp->token[i] == '$' && !is_separator(temp->token[i + 1])
		&& !is_var_enclosed_in_quotes(temp->token, i)
		&& (temp->status == NORMAL_MODE || temp->status == DOUBLE_QUOTE));
}

int	expand_variables(t_main *main_data, t_token **token_lst)
{
	t_token	*temp;
	int		i;

	temp = *token_lst;
	while (temp)
	{
		if (temp->type == VAR_TOKEN)
		{
			i = 0;
			while (temp->token[i])
			{
				toggle_quote_mode(&temp, temp->token[i]);
				if (should_expand_var(temp, i))
					process_variable_replacement(&temp,
						resolve_variable_value(temp, temp->token + i,
							main_data), i);
				else
					i++;
			}
		}
		temp = temp->next;
	}
	return (0);
}

char	*expand_variables_in_heredoc(t_main *main_data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_separator(str[i + 1]) == false
			&& is_var_enclosed_in_quotes(str, i) == false)
			str = replace_variable_in_heredoc(str, resolve_variable_value(NULL,
						str + i, main_data), i);
		else
			i++;
	}
	return (str);
}
