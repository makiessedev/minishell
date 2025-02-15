#include "minishell.h"

int	tokenization(t_data *data, char *str)
{
	int	i;
	int	end;
	int	start;
	int	status;

	i = -1;
	start = 0;
	end = ft_strlen(str);
	status = DEFAULT;
	while (++i <= end)
	{
		status = set_status(status, str, i);
		if (status == DEFAULT)
			start = save_word_or_sep(&i, str, start, data);
	}
	if (status != DEFAULT)
	{
		if (status == DQUOTE)
			errmsg("unexpected EOF while looking for matching", "\"", true);
		else if (status == SQUOTE)
			errmsg("unexpected EOF while looking for matching", "\'", true);
		errmsg("syntax error", "unexpected end of file", false);
		return (1);
	}
	return (0);
}
