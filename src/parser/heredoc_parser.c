/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:55:50 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:58:46 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool get_heredoc(t_main *main_data, t_io_fds *io) {
  int tmp_fd;
  bool ret;

  ret = true;
  tmp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
  ret = fill_heredoc(main_data, io, tmp_fd);
  close(tmp_fd);
  return (ret);
}

static char *generate_heredoc_path(void) {
  static int i;
  char *name;
  char *number;

  number = ft_itoa(i);
  if (!number)
    return (NULL);
  name = ft_strjoin("/tmp/minishell_heredoc_", number);
  free(number);
  i++;
  return (name);
}

static char *get_delimiter(char *delim, bool *quotes) {
  int len;

  len = ft_strlen(delim) - 1;
  if ((delim[0] == '\"' && delim[len] == '\"') ||
      (delim[0] == '\'' && delim[len] == '\'')) {
    *quotes = true;
    return (ft_strtrim(delim, "\'\""));
  }
  return (ft_strdup(delim));
}

void parse_heredoc(t_main *main_data, t_command **last_cmd,
                   t_token **token_lst) {
  t_token *temp;
  t_command *cmd;
  t_io_fds *io;

  temp = *token_lst;
  cmd = lst_last_cmd(*last_cmd);
  init_io(cmd);
  io = cmd->io_fds;
  if (!remove_old_file_ref(io, true))
    return;
  io->infile = generate_heredoc_path();
  io->heredoc_delimiter =
      get_delimiter(temp->next->token, &(io->heredoc_quotes));
  if (get_heredoc(main_data, io))
    io->fd_in = open(io->infile, O_RDONLY);
  else
    io->fd_in = -1;
  if (temp->next->next)
    temp = temp->next->next;
  else
    temp = temp->next;
  *token_lst = temp;
}
