#include "minishell.h"

int	process_variable_replacement(t_token **token_node, char *var_value, int index)
{
	if (var_value == NULL)
	{
		if (remove_variable(token_node, (*token_node)->token, index) == 1)
		{
			erase_pointer(var_value);
			return (1);
		}
	}
	else
	{
		if (replace_variable(token_node, (*token_node)->token, \
		var_value, index) == NULL)
		{
			erase_pointer(var_value);
			return (1);
		}
	}
	erase_pointer(var_value);
	return (0);
}

char	*replace_variable_in_heredoc(char *str, char *var_value, int index)
{
	char	*tmp;

	tmp = NULL;
	if (var_value == NULL)
		*str = '\0';
	else
	{
		tmp = str;
		str = replace_variable(NULL, str, var_value, index);
		erase_pointer(tmp);
	}
	erase_pointer(var_value);
	return (str);
}
