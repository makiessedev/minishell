/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:53:08 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:57:46 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_env(t_main *main_data, char **args) {
  int i;

  if (args && args[1])
    return (throw_command_error("env", NULL, "too many arguments", 2));
  i = 0;
  if (!main_data->env)
    return (EXIT_FAILURE);
  while (main_data->env[i])
    ft_putendl_fd(main_data->env[i++], STDOUT_FILENO);
  return (EXIT_SUCCESS);
}
