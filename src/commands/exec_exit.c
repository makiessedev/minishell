/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:53:14 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/26 21:03:01 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int handle_exit_code(char **args, int *error) {
  int exit_code;

  if (!args || !args[1])
    return (g_exit_code);
  exit_code = get_exit_code(args[1], error);
  if (*error)
    return (
        throw_command_error("exit", args[1], "numeric argument required", 2));
  if (args[2])
    return (throw_command_error("exit", NULL, "too many arguments", 1));
  return (exit_code);
}*/
/*
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
*/
static int *exit_status_pointer(void);

int exec_exit_status_get(void) { return (*exit_status_pointer()); }

void exec_exit_status_set(int status) {
  if (status == EXIT_FAILURE)
    status = EXIT_FAILURE;
  *exit_status_pointer() = status;
}

static int *exit_status_pointer(void) {
  static int last_exit_status = 0;

  return (&last_exit_status);
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

int builtin_exit(int argc, char **argv) {
  int exit_num;

  /*	if (!subshell && isatty(STDERR_FILENO))
                  ft_putstr_fd("exit\n", STDERR_FILENO);
          */
  exit_num = exec_exit_status_get();
  if (argc >= 2 && num_is_numeric(argv[1]) == FALSE)
    exit_num = 255;
  else if (argc == 2)
    exit_num = ft_atoi(argv[1]);
  else if (argc > 2) {
    throw_command_error("exit", NULL, "too many arguments", 1);
    return (EXIT_FAILURE);
  }
  exit(exit_num);
}

int exec_exit(t_main *main_data, char **args) {
  /*int exit_code;
  int error;
  int quiet;

  error = FALSE;
  quiet = is_quiet_mode(main_data);
  if (!quiet)
    ft_putendl_fd("exit", 2);
  exit_code = handle_exit_code(args, &error);
  if (error && args[2])
    return (exit_code);
  update_shell_level(main_data);
  erase_and_exit_shell(main_data, exit_code);*/
  (void)main_data;
  return (builtin_exit(count_tab(args), args));
  // return (2);
}
