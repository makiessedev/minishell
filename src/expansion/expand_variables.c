#include "minishell.h"

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
