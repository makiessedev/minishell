#include "minishell.h"

int	tokenization(t_main *main_data, char *str)
{
	int	i;
	int	end;
	int	start;
	int	status;

	i = -1;
	start = 0;
	end = ft_strlen(str);
	status = NORMAL_MODE;
	while (++i <= end)
	{
		status = set_status(status, str, i);
		if (status == NORMAL_MODE)
			start = save_word_or_sep(&i, str, start, main_data);
	}
	if (status != NORMAL_MODE)
	{
		if (status == DOUBLE_QUOTE)
			throw_message_error("unexpected EOF while looking for matching", "\"", true);
		else if (status == SINGLE_QUOTE)
			throw_message_error("unexpected EOF while looking for matching", "\'", true);
		throw_message_error("syntax error", "unexpected end of file", false);
		return (1);
	}
	return (0);
}
