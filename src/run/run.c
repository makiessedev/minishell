/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:56:29 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/19 23:47:45 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int get_children(t_main *main_data)
{
  pid_t wpid;
  int status;
  int save_status;

  close_fds(main_data->cmd, false);
  save_status = 0;
  wpid = 0;
  while (wpid != -1) {
    wpid = waitpid(-1, &status, 0);
    if (wpid == main_data->pid)
      save_status = status;
  }
  return (save_status);
}

void set_break()
{
  char *shell_level;
  shell_level = getenv("SHLVL");
  if(shell_level && ft_atoi(shell_level) >= 2)
    printf("\n");
}

void setup_shell_signals(t_command *cmd)
{
  struct sigaction sa_int;

  if(strncmp(cmd->command, "./minishell", ft_strlen("./minishell")) == 0)
    sa_int.sa_handler = SIG_IGN;
  else
    sa_int.sa_handler = &set_break;
  sigemptyset(&sa_int.sa_mask);
  sa_int.sa_flags = SA_RESTART;
  sigaction(SIGINT, &sa_int, NULL);
}

static int create_children(t_main *main_data) {
  t_command *cmd;

  cmd = main_data->cmd;
  while (main_data->pid != 0 && cmd) {
    main_data->pid = fork();

    if (main_data->pid == -1)
      return (throw_command_error("fork", NULL, "error on fork", EXIT_FAILURE));
    else if (main_data->pid == 0)
      run_command(main_data, cmd);
    else
      setup_shell_signals(cmd);
    cmd = cmd->next;
  }
  return (get_children(main_data));
}

static int prep_for_exec(t_main *main_data) {
  if (!main_data || !main_data->cmd)
    return (EXIT_SUCCESS);
  if (!main_data->cmd->command) {
    if (main_data->cmd->io_fds && !check_infile_outfile(main_data->cmd->io_fds))
      return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
  }
  if (!initialize_command_pipes(main_data))
    return (EXIT_FAILURE);
  return (CMD_NOT_FOUND);
}

int run(t_main *main_data) {
  int ret;

  ret = prep_for_exec(main_data);
  if (ret != CMD_NOT_FOUND)
    return (ret);
  if (!main_data->cmd->pipe_output && !main_data->cmd->prev &&
      check_infile_outfile(main_data->cmd->io_fds)) {
    redirect_standard_streams(main_data->cmd->io_fds);
    ret = run_builtin(main_data, main_data->cmd);
    restore_standard_streams(main_data->cmd->io_fds);
  }
  if (ret != CMD_NOT_FOUND)
    return (ret);
  return (create_children(main_data));
}
