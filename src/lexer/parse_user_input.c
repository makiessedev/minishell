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

bool	parse_user_input(t_main *main_data)
{
	if (main_data->user_input == NULL)
		exit_builtin(main_data, NULL);
	else if (ft_strncmp(main_data->user_input, "\0", 1) == 0)
		return (false);
	else if (input_is_space(main_data->user_input))
		return (true);
	add_history(main_data->user_input);
	if (tokenization(main_data, main_data->user_input) == FAILURE)
		return (false);
	if (main_data->token->type == END_TOKEN)
		return (false);
	if (check_if_var(&main_data->token) == FAILURE)
		return (false);
	var_expander(main_data, &main_data->token);
	handle_quotes(main_data);
	create_commands(main_data, main_data->token);
	return (true);
}
