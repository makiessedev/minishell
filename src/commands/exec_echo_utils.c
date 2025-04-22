/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:53:04 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/22 05:46:59 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_n_flag(char *arg) {
  int i;
  int n_flag;

  n_flag = FALSE;
  i = 0;

  if (arg[i] != '-' || (arg[i] == '-' && arg[i + 1] != 'n')) {
    return (n_flag);
  }
  i++;
  while (arg[i] && arg[i] == 'n')
    i++;
  if (arg[i] == '\0')
    n_flag = TRUE;
  return (n_flag);
}

void echo_print_args(char **args, int n_flag, int i) {
  if (!args[i]) {
    if (!n_flag)
      ft_putchar_fd('\n', STDOUT_FILENO);
    return;
  }
  while (args[i]) {
    ft_putstr_fd(args[i], STDOUT_FILENO);
    if (args[i + 1])
      ft_putchar_fd(' ', STDOUT_FILENO);
    else if (!args[i + 1] && !n_flag)
      ft_putchar_fd('\n', STDOUT_FILENO);
    i++;
  }
}
