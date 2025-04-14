/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:53:14 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:57:47 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_exit(t_main *main_data, char **args) {
  int exit_code;
  bool error;
  bool quiet;

  quiet = is_quiet_mode(main_data);
  error = false;
  if (!quiet)
    ft_putendl_fd("exit", 2);
  if (!args || !args[1])
    exit_code = g_exit_code;
  else {
    exit_code = get_exit_code(args[1], &error);
    if (error)
      exit_code =
          throw_command_error("exit", args[1], "numeric argument required", 2);
    else if (args[2])
      return (throw_command_error("exit", NULL, "too many arguments", 1));
  }
  erase_and_exit_shell(main_data, exit_code);
  return (2);
}
