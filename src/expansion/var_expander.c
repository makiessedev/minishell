#include "minishell.h"

static void	update_status(t_token **token_node, char c)
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

static bool	is_next_char_a_sep(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (true);
	else
		return (false);
}

static bool	var_between_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (str[i - 1] == '\"' && str[i + 1] == '\"')
			return (true);
		else
			return (false);
	}
	return (false);
}

int	var_expander(t_main *main_data, t_token **token_lst)
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
				update_status(&temp, temp->token[i]);
				if (temp->token[i] == '$'
					&& is_next_char_a_sep(temp->token[i + 1]) == false
					&& var_between_quotes(temp->token, i) == false
					&& (temp->status == NORMAL_MODE || temp->status == DOUBLE_QUOTE))
					replace_var(&temp,
						recover_val(temp, temp->token + i, main_data), i);
				else
					i++;
			}
		}
		temp = temp->next;
	}
	return (0);
}

char	*var_expander_heredoc(t_main *main_data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$'
			&& is_next_char_a_sep(str[i + 1]) == false
			&& var_between_quotes(str, i) == false)
			str = replace_str_heredoc(str, recover_val(NULL, str + i, main_data), i);
		else
			i++;
	}
	return (str);
}
