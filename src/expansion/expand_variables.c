#include "minishell.h"

static void	toggle_quote_mode(t_token **token_node, char c)
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

static bool	is_separator(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (true);
	else
		return (false);
}

static bool	is_var_enclosed_in_quotes(char *str, int i)
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
				if (temp->token[i] == '$'
					&& is_separator(temp->token[i + 1]) == false
					&& is_var_enclosed_in_quotes(temp->token, i) == false
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

char	*expand_variables_in_heredoc(t_main *main_data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$'
			&& is_separator(str[i + 1]) == false
			&& is_var_enclosed_in_quotes(str, i) == false)
			str = replace_str_heredoc(str, recover_val(NULL, str + i, main_data), i);
		else
			i++;
	}
	return (str);
}
