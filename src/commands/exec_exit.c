/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:53:14 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/26 21:30:56 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void update_shell_level(t_main *main_data) {
  int shell_level;
  char *new_lvl;

  shell_level = ft_atoi(getenv("SHLVL"));
  if (shell_level == 1)
    return;
  new_lvl = ft_itoa(--shell_level);
  if (new_lvl)
    update_or_create_env_variable(main_data, "SHLVL", new_lvl);
  free(new_lvl);
}

static int num_is_numeric(char *str) {
  int i;

  i = 0;
  if (str[0] == '\0') {
    throw_command_error("exit", str, "numeric argument required", 2);
    return (FALSE);
  } else if ((str[0] == '-' || str[0] == '+') && str[1] != '\0')
    i++;
  while (str[i]) {
    if (!ft_isdigit(str[i])) {
      throw_command_error("exit", str, "numeric argument required", 2);
      return (FALSE);
    }
    i++;
  }
  return (TRUE);
}

int builtin_exit(t_main *main_data, int argc, char **argv) {
  int exit_num;
  int quiet;

  quiet = is_quiet_mode(main_data);
  if (!quiet)
    ft_putendl_fd("exit", 2);
  exit_num = g_exit_code;
  if (argc >= 2 && num_is_numeric(argv[1]) == FALSE)
    exit_num = 255;
  else if (argc == 2)
    exit_num = ft_atoi(argv[1]);
  else if (argc > 2) {
    throw_command_error("exit", NULL, "too many arguments", 1);
    return (EXIT_FAILURE);
  }
  update_shell_level(main_data);
  erase_and_exit_shell(main_data, exit_num);
  return (EXIT_FAILURE);
}

int exec_exit(t_main *main_data, char **argv) {

  int exit_num;
  int quiet;
  int argc;

  argc = count_tab(argv);
  quiet = is_quiet_mode(main_data);
  if (!quiet)
    ft_putendl_fd("exit", 2);
  exit_num = g_exit_code;
  if (argc >= 2 && num_is_numeric(argv[1]) == FALSE)
    exit_num = 255;
  else if (argc == 2)
    exit_num = ft_atoi(argv[1]);
  else if (argc > 2) {
    throw_command_error("exit", NULL, "too many arguments", 1);
    return (EXIT_FAILURE);
  }
  update_shell_level(main_data);
  erase_and_exit_shell(main_data, exit_num);
  return (EXIT_FAILURE);
}
