/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:54:07 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:58:04 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void close_fds(t_command *cmds, bool close_backups) {
  if (cmds->io_fds) {
    if (cmds->io_fds->fd_in != -1)
      close(cmds->io_fds->fd_in);
    if (cmds->io_fds->fd_out != -1)
      close(cmds->io_fds->fd_out);
    if (close_backups)
      restore_standard_streams(cmds->io_fds);
  }
  close_unused_pipes(cmds, NULL);
}
