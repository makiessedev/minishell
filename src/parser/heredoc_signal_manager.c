/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal_manager.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 01:10:30 by zombunga          #+#    #+#             */
/*   Updated: 2025/04/27 01:42:22 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void signal_ctlc_heredoc(int sig) {
  if (sig == SIGINT) {
    close(STDIN_FILENO);
    write(STDERR_FILENO, "\n", 1);
  }
}

int check_error(int stdin) {

  if (errno == EBADF) {
    dup2(stdin, STDIN_FILENO);
    close(stdin);
    errno = 0;
    return (FALSE);
  }
  return (TRUE);
}
