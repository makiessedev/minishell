#include "minishell.h"

int	tokenization(t_main *main_data)
{
	int	i;
	int	end;
	int	start;
	int	status;

	i = -1;
	start = 0;
	end = ft_strlen(main_data->user_input);
	status = NORMAL_MODE;
	while (++i <= end)
	{
		status = check_status_quote(status, main_data->user_input, i);
		if (status == NORMAL_MODE)
			start = save_word_or_sep(&i, main_data->user_input, start, main_data);
	}
	if (status != NORMAL_MODE)
	{
		if (status == DOUBLE_QUOTE || status == SINGLE_QUOTE)
			throw_message_error("unexpected EOF while looking for matching", "\"", true);
		throw_message_error("syntax error", "unexpected end of file", false);
		return (1);
	}
	return (0);
}
