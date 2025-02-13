#include "minishell.h"

static bool	contains_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (true);
		i++;
	}
	return (false);
}

static void	split_var_cmd_token(t_command *last_cmd, char *cmd_str)
{
	t_token		*new_tokens;
	t_token		*tmp;
	char		**strs;
	int			i;

	new_tokens = NULL;
	strs = ft_split(cmd_str, ' ');
	if (!strs)
		return ;
	last_cmd->command = ft_strdup(strs[0]);
	if (strs[1])
		new_tokens = lst_new_token(ft_strdup(strs[1]), NULL, WORD_TOKEN, NORMAL_MODE);
	tmp = new_tokens;
	i = 1;
	while (strs[++i])
		lst_add_back_token(&new_tokens,
			lst_new_token(ft_strdup(strs[i]), NULL, WORD_TOKEN, NORMAL_MODE));
	lst_add_back_token(&new_tokens,
		lst_new_token(NULL, NULL, END_TOKEN, NORMAL_MODE));
	fill_args(&new_tokens, last_cmd);
	lstclear_token(&tmp, &free_ptr);
	free_str_tab(strs);
}

void	parse_word(t_command **cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*last_cmd;

	temp = *token_lst;
	while (temp->type == WORD_TOKEN || temp->type == VAR_TOKEN)
	{
		last_cmd = lst_last_cmd(*cmd);
		if (temp->prev == NULL || (temp->prev && temp->prev->type == PIPE_TOKEN)
			|| last_cmd->command == NULL)
		{
			if (temp->type == VAR_TOKEN && contains_space(temp->token))
				split_var_cmd_token(last_cmd, temp->token);
			else
				last_cmd->command = ft_strdup(temp->token);
			temp = temp->next;
		}
		else
			fill_args(&temp, last_cmd);
	}
	*token_lst = temp;
}
