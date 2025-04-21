/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:55:05 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 22:05:26 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_enclosed_in_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (str[i - 1] == '\"' && str[i + 1] == '\"')
			return (TRUE);
		else
			return (FALSE);
	}
	return (FALSE);
}

int	is_separator(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (TRUE);
	else
		return (FALSE);
}

void	toggle_quote_mode(t_token **token_node, char c)
{
	if (c == '\'' && (*token_node)->status == NORMAL_MODE)
		(*token_node)->status = SINGLE_QUOTE;
	else if (c == '\"' && (*token_node)->status == NORMAL_MODE)
		(*token_node)->status = DOUBLE_QUOTE;
	else if (c == '\'' && (*token_node)->status == SINGLE_QUOTE)
		(*token_node)->status = NORMAL_MODE;
	else if (c == '\"' && (*token_node)->status == DOUBLE_QUOTE)
		(*token_node)->status = NORMAL_MODE;
}

int	remove_variable(t_token **token_node, char *str, int index)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = 0;
	j = 0;
	len = ft_strlen(str) - var_length(str + index);
	new_str = (char *)malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (1);
	while (str[i])
	{
		if (str[i] == '$' && i == index)
		{
			i = i + var_length(str + index) + 1;
			if (str[i] == '\0')
				break ;
		}
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	erase_pointer((*token_node)->token);
	(*token_node)->token = new_str;
	return (0);
}

char	*replace_variable(t_token **token_node, char *str, char *var_value,
		int index)
{
	char	*newstr;
	int		newstr_size;

	newstr_size = (ft_strlen(str) - var_length(str + index)
			+ ft_strlen(var_value));
	newstr = get_new_token_string(str, var_value, newstr_size, index);
	if (token_node && *token_node)
	{
		erase_pointer((*token_node)->token);
		(*token_node)->token = newstr;
	}
	return (newstr);
}
