/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:55:28 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:58:37 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void close_unused_pipes(t_command *cmds, t_command *skip_cmd) {
  while (cmds) {
    if (cmds != skip_cmd && cmds->pipe_fd) {
      close(cmds->pipe_fd[0]);
      close(cmds->pipe_fd[1]);
    }
    cmds = cmds->next;
  }
}

bool initialize_command_pipes(t_main *main_data) {
  int *fd;
  t_command *tmp;

  tmp = main_data->cmd;
  while (tmp) {
    if (tmp->pipe_output || (tmp->prev && tmp->prev->pipe_output)) {
      fd = malloc(sizeof *fd * 2);
      if (!fd || pipe(fd) != 0) {
        erase_main_data(main_data, false);
        return (false);
      }
      tmp->pipe_fd = fd;
    }
    tmp = tmp->next;
  }
  return (true);
}

bool connect_command_pipes(t_command *cmds, t_command *c) {
  if (!c)
    return (false);
  if (c->prev && c->prev->pipe_output)
    dup2(c->prev->pipe_fd[0], STDIN_FILENO);
  if (c->pipe_output)
    dup2(c->pipe_fd[1], STDOUT_FILENO);
  close_unused_pipes(cmds, c);
  return (true);
}
