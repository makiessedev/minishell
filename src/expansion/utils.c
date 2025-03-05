#include "minishell.h"

bool	is_var_enclosed_in_quotes(char *str, int i)
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

bool	is_separator(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (true);
	else
		return (false);
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