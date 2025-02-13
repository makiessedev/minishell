#include "minishell.h"

static bool	input_is_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	parse_user_input(t_minishell *data)
{
	if (data->input_user == NULL)
		exit_builtin(data, NULL);
	else if (ft_strcmp(data->input_user, "\0") == 0)
		return (false);
	else if (input_is_space(data->input_user))
		return (true);
	add_history(data->input_user);
	if (tokenization(data, data->input_user) == FAILURE)
		return (false);
	if (data->token->type == END_TOKEN)
		return (false);
	if (check_if_var(&data->token) == FAILURE)
		return (false);
	var_expander(data, &data->token);
	handle_quotes(data);
	create_commands(data, data->token);
	return (true);
}
