/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:55:43 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:58:43 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void initialize_cmd(t_command **cmd) {
  (*cmd)->command = NULL;
  (*cmd)->path = NULL;
  (*cmd)->args = NULL;
  (*cmd)->pipe_output = false;
  (*cmd)->pipe_fd = 0;
  (*cmd)->prev = NULL;
  (*cmd)->next = NULL;
}

t_command *lst_new_cmd(bool value) {
  t_command *new_node;

  new_node = (t_command *)malloc(sizeof(t_command));
  if (!(new_node))
    return (NULL);
  ft_memset(new_node, 0, sizeof(t_command));
  new_node->pipe_output = value;
  initialize_cmd(&new_node);
  return (new_node);
}

void lst_add_back_cmd(t_command **alst, t_command *new_node) {
  t_command *start;

  start = *alst;
  if (start == NULL) {
    *alst = new_node;
    return;
  }
  if (alst && *alst && new_node) {
    while (start->next != NULL)
      start = start->next;
    start->next = new_node;
    new_node->prev = start;
  }
}

t_command *lst_last_cmd(t_command *cmd) {
  while (cmd->next != NULL)
    cmd = cmd->next;
  return (cmd);
}
