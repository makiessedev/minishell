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

int	create_args_NORMAL_MODE_mode(t_token **token_node, t_command *last_cmd)
{
	int		i;
	int		nb_args;
	t_token	*temp;

	i = 0;
	temp = *token_node;
	nb_args = count_arguments(temp);
	last_cmd->args = malloc(sizeof(char *) * (nb_args + 2));
	if (!last_cmd->args)
		return (FAILURE);
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
	return (SUCCESS);
}

static char	**copy_NORMAL_MODE_in_new_tab(
	int len, char **new_tab, t_command *last_cmd, t_token **tk_node)
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

int	add_args_NORMAL_MODE_mode(t_token **token_node, t_command *last_cmd)
{
	int		i;
	int		len;
	char	**new_tab;
	t_token	*temp;

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
		return (FAILURE);
	new_tab = copy_NORMAL_MODE_in_new_tab(len, new_tab, last_cmd, token_node);
	free(last_cmd->args);
	last_cmd->args = new_tab;
	*token_node = temp;
	return (SUCCESS);
}

int	fill_args(t_token **token_node, t_command *last_cmd)
{
	if (!ft_strcmp(last_cmd->command, "echo"))
	{
		if (!(last_cmd->args))
			return (create_args_echo_mode(token_node, last_cmd));
		else
			return (add_args_echo_mode(token_node, last_cmd));
	}
	else
	{
		if (last_cmd && !(last_cmd->args))
			return (create_args_NORMAL_MODE_mode(token_node, last_cmd));
		else
			return (add_args_NORMAL_MODE_mode(token_node, last_cmd));
	}
	return (SUCCESS);
}
