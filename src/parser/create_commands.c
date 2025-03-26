#include "minishell.h"

static void	prep_no_arg_commands(t_main *main_data)
{
	t_command	*cmd;

	if (!main_data || !main_data->cmd)
		return ;
	cmd = main_data->cmd;
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
	cmd = lst_last_cmd(main_data->cmd);
}

void	create_commands(t_main *main_data, t_token *token)
{
	t_token	*temp;

	temp = token;
	if (temp->type == END_TOKEN)
		return ;
	while (temp->next != NULL)
	{
		if (temp == token)
			lst_add_back_cmd(&main_data->cmd, lst_new_cmd(false));
		if (temp->type == WORD_TOKEN || temp->type == VAR_TOKEN)
			word_parser(&main_data->cmd, &temp);
		else if (temp->type == INPUT_TOKEN)
			input_parser(&main_data->cmd, &temp);
		else if (temp->type == REDIRECT_TOKEN)
			redirect_parser(&main_data->cmd, &temp);
		else if (temp->type == HEREDOC_TOKEN)
			parse_heredoc(main_data, &main_data->cmd, &temp);
		else if (temp->type == APPEND_TOKEN)
			append_parser(&main_data->cmd, &temp);
		else if (temp->type == PIPE_TOKEN)
			pipe_parser(&main_data->cmd, &temp);
		else if (temp->type == END_TOKEN)
			break ;
	}
	prep_no_arg_commands(main_data);
}
