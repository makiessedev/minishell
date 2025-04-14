/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:56:11 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:58:54 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int remove_quotes(t_token **token_node) {
  char *new_line;
  int i;
  int j;

  i = 0;
  j = 0;
  new_line = malloc(sizeof(char) * calculate_length_without_quotes(
                                       (*token_node)->token, i, i));
  if (!new_line)
    return (1);
  while ((*token_node)->token[i]) {
    if (is_quotes_and_normal_mode(token_node, i) == true) {
      set_quote_mode(token_node, &i);
      continue;
    } else if (reset_to_normal_mode(token_node, &i) == true)
      continue;
    new_line[j++] = (*token_node)->token[i++];
  }
  new_line[j] = '\0';
  erase_pointer((*token_node)->token);
  (*token_node)->token = new_line;
  return (0);
}

int process_and_remove_quotes(t_main *main_data) {
  t_token *temp;

  temp = main_data->token;
  while (temp) {
    if (contains_quotes(temp->token) == true &&
        (!temp->prev || (temp->prev && temp->prev->type != HEREDOC_TOKEN)))
      remove_quotes(&temp);
    temp = temp->next;
  }
  return (0);
}
