/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:54:13 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:58:06 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void lst_delone_cmd(t_command *lst, void (*del)(void *)) {
  if (lst->command)
    (*del)(lst->command);
  if (lst->args)
    erase_tab_string(lst->args);
  if (lst->pipe_fd)
    (*del)(lst->pipe_fd);
  if (lst->io_fds)
    erase_input_output(lst->io_fds);
  (*del)(lst);
}

void lst_clear_cmd(t_command **lst, void (*del)(void *)) {
  t_command *temp;

  temp = NULL;
  while (*lst != NULL) {
    temp = (*lst)->next;
    lst_delone_cmd(*lst, del);
    *lst = temp;
  }
}
