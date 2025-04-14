/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_user_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:56:51 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:59:12 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool input_is_space(char *input) {
  int i;

  i = 0;
  while (input[i]) {
    if (!ft_isspace(input[i]))
      return (false);
    i++;
  }
  return (true);
}

bool process_user_command(t_main *main_data) {
  if (input_is_space(main_data->user_input))
    return (true);
  add_history(main_data->user_input);
  if (tokenization(main_data) == EXIT_FAILURE)
    return (false);
  if (main_data->token->type == END_TOKEN)
    return (false);
  if (validate_syntax_and_variables(&main_data->token) == EXIT_FAILURE)
    return (false);
  expand_variables(main_data, &main_data->token);
  process_and_remove_quotes(main_data);
  create_commands(main_data, main_data->token);
  return (true);
}
