/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:56:01 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/16 11:18:43 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void word_parser(t_command **cmd, t_token **token_lst) {
  t_token *temp;
  t_command *last_cmd;

  temp = *token_lst;
  while (temp->type == WORD_TOKEN || temp->type == VAR_TOKEN) {
    last_cmd = lst_last_cmd(*cmd);
    if (temp->prev == NULL || (temp->prev && temp->prev->type == PIPE_TOKEN) ||
        last_cmd->command == NULL) {
      last_cmd->command = ft_strdup(temp->token);
      temp = temp->next;
    } else
      populate_command_args(&temp, last_cmd);
  }
  *token_lst = temp;
}

void redirect_parser(t_command **last_cmd, t_token **token_lst) {
  t_token *temp;
  t_command *cmd;

  temp = *token_lst;
  cmd = lst_last_cmd(*last_cmd);
  init_io(cmd);
  open_outfile_trunc(cmd->io_fds, temp->next->token, temp->next->backup_token);
  if (temp->next->next)
    temp = temp->next->next;
  else
    temp = temp->next;
  *token_lst = temp;
}

void pipe_parser(t_command **cmd, t_token **token_lst) {
  t_command *last_cmd;

  last_cmd = lst_last_cmd(*cmd);
  last_cmd->pipe_output = true;
  lst_add_back_cmd(&last_cmd, lst_new_cmd(false));
  *token_lst = (*token_lst)->next;
}

void input_parser(t_command **last_cmd, t_token **token_lst) {
  t_token *temp;
  t_command *cmd;

  temp = *token_lst;
  cmd = lst_last_cmd(*last_cmd);
  init_io(cmd);
  open_infile(cmd->io_fds, temp->next->token, temp->next->backup_token);
  if (temp->next->next)
    temp = temp->next->next;
  else
    temp = temp->next;
  *token_lst = temp;
}

void append_parser(t_command **last_cmd, t_token **token_lst) {
  t_token *temp;
  t_command *cmd;

  temp = *token_lst;
  cmd = lst_last_cmd(*last_cmd);
  init_io(cmd);
  open_outfile_append(cmd->io_fds, temp->next->token, temp->next->backup_token);
  if (temp->next->next)
    temp = temp->next->next;
  else
    temp = temp->next;
  *token_lst = temp;
}
