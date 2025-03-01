#include "minishell.h"

static void	change_status_to_quote(t_token **token_node, int *i)
{
	if ((*token_node)->token[*i] == '\'')
		(*token_node)->status = SINGLE_QUOTE;
	if ((*token_node)->token[*i] == '\"')
		(*token_node)->status = DOUBLE_QUOTE;
	(*i)++;
}

static bool	if_quotes_and_default(t_token **token_node, int i)
{
	if (((*token_node)->token[i] == '\'' || (*token_node)->token[i] == '\"')
		&& (*token_node)->status == NORMAL_MODE)
		return (true);
	else
		return (false);
}

static bool	change_back_to_default(t_token **token_node, int *i)
{
	if (((*token_node)->token[*i] == '\'' && (*token_node)->status == SINGLE_QUOTE)
		|| ((*token_node)->token[*i] == '\"' && (*token_node)->status == DOUBLE_QUOTE))
	{
		(*token_node)->status = NORMAL_MODE;
		(*i)++;
		return (true);
	}
	else
		return (false);
}

int	remove_quotes(t_token **token_node)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * count_len((*token_node)->token, i, i));
	if (!new_line)
		return (1);
	while ((*token_node)->token[i])
	{
		if (if_quotes_and_default(token_node, i) == true)
		{
			change_status_to_quote(token_node, &i);
			continue ;
		}
		else if (change_back_to_default(token_node, &i) == true)
			continue ;
		new_line[j++] = (*token_node)->token[i++];
	}
	new_line[j] = '\0';
	erase_pointer((*token_node)->token);
	(*token_node)->token = new_line;
	(*token_node)->join = true;
	return (0);
}
