#include "minishell.h"

void parse_word(t_command **cmd, t_token **token_lst) {
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
      fill_args(&temp, last_cmd);
  }
  *token_lst = temp;
}

void parse_trunc(t_command **last_cmd, t_token **token_lst) {
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

void parse_pipe(t_command **cmd, t_token **token_lst) {
  t_command *last_cmd;

  last_cmd = lst_last_cmd(*cmd);
  last_cmd->pipe_output = true;
  lst_add_back_cmd(&last_cmd, lst_new_cmd(false));
  *token_lst = (*token_lst)->next;
}

void parse_input(t_command **last_cmd, t_token **token_lst) {
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

void parse_append(t_command **last_cmd, t_token **token_lst) {
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
