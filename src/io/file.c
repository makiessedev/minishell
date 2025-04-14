/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:55:25 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:58:34 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool restore_standard_streams(t_io_fds *io) {
  int ret;

  ret = true;
  if (!io)
    return (ret);
  if (io->stdin_backup != -1) {
    if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
      ret = false;
    close(io->stdin_backup);
    io->stdin_backup = -1;
  }
  if (io->stdout_backup != -1) {
    if (dup2(io->stdout_backup, STDOUT_FILENO) == -1)
      ret = false;
    close(io->stdout_backup);
    io->stdout_backup = -1;
  }
  return (ret);
}

bool redirect_standard_streams(t_io_fds *io) {
  int ret;

  ret = true;
  if (!io)
    return (ret);
  io->stdin_backup = dup(STDIN_FILENO);
  if (io->stdin_backup == -1)
    ret = throw_command_error("dup", "stdin backup", "stdin backup", false);
  io->stdout_backup = dup(STDOUT_FILENO);
  if (io->stdout_backup == -1)
    ret = throw_command_error("dup", "stdout backup", "stdout backup", false);
  if (io->fd_in != -1)
    if (dup2(io->fd_in, STDIN_FILENO) == -1)
      ret = throw_command_error("dup2", io->infile, "dup2 failure", false);
  if (io->fd_out != -1)
    if (dup2(io->fd_out, STDOUT_FILENO) == -1)
      ret = throw_command_error("dup2", io->outfile, "dup2 failure", false);
  return (ret);
}

bool check_infile_outfile(t_io_fds *io) {
  if (!io || (!io->infile && !io->outfile))
    return (true);
  if ((io->infile && io->fd_in == -1) || (io->outfile && io->fd_out == -1))
    return (false);
  return (true);
}
