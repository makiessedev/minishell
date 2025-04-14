/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:56:46 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:59:10 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *lst_new_token(char *token, char *token_backup, int type, int status) {
  t_token *new_node;

  new_node = malloc(sizeof(t_token) * 1);
  if (!(new_node))
    return (NULL);
  new_node->token = token;
  new_node->backup_token = token_backup;
  new_node->var_exists = false;
  new_node->type = type;
  new_node->status = status;
  new_node->prev = NULL;
  new_node->next = NULL;
  return (new_node);
}

void lst_add_back_token(t_token **alst, t_token *new_node) {
  t_token *start;

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

void lstdelone_token(t_token *lst, void (*del)(void *)) {
  if (del && lst && lst->token) {
    (*del)(lst->token);
    lst->token = NULL;
  }
  if (del && lst && lst->backup_token) {
    (*del)(lst->backup_token);
    lst->backup_token = NULL;
  }
  if (lst->prev)
    lst->prev->next = lst->next;
  if (lst->next)
    lst->next->prev = lst->prev;
  erase_pointer(lst);
}

void lstclear_token(t_token **lst, void (*del)(void *)) {
  t_token *tmp;

  tmp = NULL;
  while (*lst != NULL) {
    tmp = (*lst)->next;
    lstdelone_token(*lst, del);
    *lst = tmp;
  }
}
