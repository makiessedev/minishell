/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_user_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:56:51 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 22:05:26 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	input_is_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	process_user_command(t_main *main_data)
{
	if (input_is_space(main_data->user_input))
		return (TRUE);
	add_history(main_data->user_input);
	if (tokenization(main_data) == EXIT_FAILURE)
		return (FALSE);
	if (main_data->token->type == END_TOKEN)
		return (FALSE);
	if (validate_syntax_and_variables(&main_data->token) == EXIT_FAILURE)
		return (FALSE);
	expand_variables(main_data, &main_data->token);
	process_and_remove_quotes(main_data);
	create_commands(main_data, main_data->token);
	return (TRUE);
}
