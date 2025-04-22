/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_to_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:55:57 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 20:24:41 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**conpy_and_extend_args(int len, char **new_tab,
		t_command *last_cmd, t_token **tk_node)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = *tk_node;
	while (i < len)
	{
		new_tab[i] = last_cmd->args[i];
		i++;
	}
	while (temp->type == WORD_TOKEN || temp->type == VAR_TOKEN)
	{
		new_tab[i] = ft_strdup(temp->token);
		i++;
		temp = temp->next;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

int	initialize_command_args(t_token **token_node, t_command *last_cmd)
{
	int		i;
	int		nb_args;
	t_token	*temp;

	remove_empty_variable_arguments(token_node);
	i = 0;
	temp = *token_node;
	nb_args = count_arguments(temp);
	last_cmd->args = malloc(sizeof(char *) * (nb_args + 2));
	if (!last_cmd->args)
		return (EXIT_FAILURE);
	temp = *token_node;
	i = 0;
	last_cmd->args[i] = ft_strdup(last_cmd->command);
	i++;
	while (temp->type == WORD_TOKEN || temp->type == VAR_TOKEN)
	{
		last_cmd->args[i] = ft_strdup(temp->token);
		i++;
		temp = temp->next;
	}
	last_cmd->args[i] = NULL;
	*token_node = temp;
	return (EXIT_SUCCESS);
}

int	append_command_args(t_token **token_node, t_command *last_cmd)
{
	int		i;
	int		len;
	char	**new_tab;
	t_token	*temp;

	remove_empty_variable_arguments(token_node);
	i = 0;
	temp = *token_node;
	while (temp->type == WORD_TOKEN || temp->type == VAR_TOKEN)
	{
		i++;
		temp = temp->next;
	}
	len = 0;
	while (last_cmd->args[len])
		len++;
	new_tab = malloc(sizeof(char *) * (i + len + 1));
	if (!new_tab)
		return (EXIT_FAILURE);
	new_tab = conpy_and_extend_args(len, new_tab, last_cmd, token_node);
	free(last_cmd->args);
	last_cmd->args = new_tab;
	*token_node = temp;
	return (EXIT_SUCCESS);
}

int	populate_command_args(t_token **token_node, t_command *last_cmd)
{
	if (last_cmd && !(last_cmd->args))
		return (initialize_command_args(token_node, last_cmd));
	else
		return (append_command_args(token_node, last_cmd));
}
