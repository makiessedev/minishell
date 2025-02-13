#include "minishell.h"

static void	prep_no_arg_commands(t_minishell *data)
{
	t_command	*cmd;

	if (!data || !data->cmd)
		return ;
	cmd = data->cmd;
	while (cmd && cmd->command)
	{
		if (!cmd->args)
		{
			cmd->args = malloc(sizeof * cmd->args * 2);
			cmd->args[0] = ft_strdup(cmd->command);
			cmd->args[1] = NULL;
		}
		cmd = cmd->next;
	}
	cmd = lst_last_cmd(data->cmd);
}

void	create_commands(t_minishell *data, t_token *token)
{
	t_token	*temp;

	temp = token;
	if (temp->type == END_TOKEN)
		return ;
	while (temp->next != NULL)
	{
		if (temp == token)
			lst_add_back_cmd(&data->cmd, lst_new_cmd(false));
		if (temp->type == WORD_TOKEN || temp->type == VAR_TOKEN)
			parse_word(&data->cmd, &temp);
		else if (temp->type == INPUT_TOKEN)
			parse_input(&data->cmd, &temp);
		else if (temp->type == REDIRECT_TOKEN)
			parse_trunc(&data->cmd, &temp);
		else if (temp->type == HEREDOC_TOKEN)
			parse_heredoc(data, &data->cmd, &temp);
		else if (temp->type == APPEND_TOKEN)
			parse_append(&data->cmd, &temp);
		else if (temp->type == PIPE_TOKEN)
			parse_pipe(&data->cmd, &temp);
		else if (temp->type == END_TOKEN)
			break ;
	}
	prep_no_arg_commands(data);
}
