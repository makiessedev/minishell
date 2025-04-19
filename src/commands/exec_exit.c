/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:53:14 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/19 23:14:38 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_exit(t_main *main_data, char **args) {
  int exit_code;
  int shell_level;
  char *shell_level_str;
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
  shell_level_str = getenv("SHLVL");
  shell_level = ft_atoi(shell_level_str);
  if (shell_level > 2)
    update_or_create_env_variable(main_data, "SHLVL", ft_itoa(--shell_level));
  erase_and_exit_shell(main_data, exit_code);
  return (2);
}
