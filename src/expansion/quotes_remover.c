#include "minishell.h"

static void	set_quote_mode(t_token **token_node, int *i)
{
	if ((*token_node)->token[*i] == '\'')
		(*token_node)->status = SINGLE_QUOTE;
	if ((*token_node)->token[*i] == '\"')
		(*token_node)->status = DOUBLE_QUOTE;
	(*i)++;
}

static bool	is_quotes_and_normal_mode(t_token **token_node, int i)
{
	if (((*token_node)->token[i] == '\'' || (*token_node)->token[i] == '\"')
		&& (*token_node)->status == NORMAL_MODE)
		return (true);
	else
		return (false);
}

static bool	reset_to_normal_mode(t_token **token_node, int *i)
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
	new_line = malloc(sizeof(char) * calculate_length_without_quotes((*token_node)->token, i, i));
	if (!new_line)
		return (1);
	while ((*token_node)->token[i])
	{
		if (is_quotes_and_normal_mode(token_node, i) == true)
		{
			set_quote_mode(token_node, &i);
			continue ;
		}
		else if (reset_to_normal_mode(token_node, &i) == true)
			continue ;
		new_line[j++] = (*token_node)->token[i++];
	}
	new_line[j] = '\0';
	erase_pointer((*token_node)->token);
	(*token_node)->token = new_line;
	(*token_node)->join = true;
	return (0);
}
