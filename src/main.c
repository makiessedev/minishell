/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:57:29 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:59:30 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void set_unused_args(int ac, char **av) {
  (void)ac;
  (void)av;
}

int main(int ac, char **av, char **env) {
  t_main main_data;

  set_unused_args(ac, av);
  ft_memset(&main_data, 0, sizeof(t_main));
  if (!init_data(&main_data, env))
    erase_and_exit_shell(NULL, EXIT_FAILURE);
  bootstrap(&main_data);
  erase_and_exit_shell(&main_data, g_exit_code);
  return (0);
}
