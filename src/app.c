/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:57:22 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:59:28 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_code;

static void update_prompt(int signo) {
  (void)signo;
  write(1, "\n", 1);
  rl_on_new_line();
  rl_replace_line("", 0);
  rl_redisplay();
}

static void ignore_sigquit(void) {
  struct sigaction act;

  ft_memset(&act, 0, sizeof(act));
  act.sa_handler = SIG_IGN;
  sigaction(SIGQUIT, &act, NULL);
}

void signals_manager(void) {
  struct sigaction act;

  ignore_sigquit();
  ft_memset(&act, 0, sizeof(act));
  act.sa_handler = &update_prompt;
  sigaction(SIGINT, &act, NULL);
}

void bootstrap(t_main *main_data) {
  while (1) {
    signals_manager();
    main_data->user_input = readline(PROMPT);
    if (main_data->user_input == NULL)
      exec_exit(main_data, NULL);
    if (process_user_command(main_data))
      g_exit_code = run(main_data);
    else
      g_exit_code = 1;
    erase_main_data(main_data, false);
  }
}
