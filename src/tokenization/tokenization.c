/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:56:54 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:59:15 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_status_quote(int status, char *str, int i) {
  if (str[i] == '\'' && status == NORMAL_MODE)
    status = SINGLE_QUOTE;
  else if (str[i] == '\"' && status == NORMAL_MODE)
    status = DOUBLE_QUOTE;
  else if (str[i] == '\'' && status == SINGLE_QUOTE)
    status = NORMAL_MODE;
  else if (str[i] == '\"' && status == DOUBLE_QUOTE)
    status = NORMAL_MODE;
  return (status);
}

int tokenization(t_main *main_data) {
  int i;
  int end;
  int start;
  int status;

  i = -1;
  start = 0;
  end = ft_strlen(main_data->user_input);
  status = NORMAL_MODE;
  while (++i <= end) {
    status = check_status_quote(status, main_data->user_input, i);
    if (status == NORMAL_MODE)
      start = storage_word_or_separator_token(&i, start, main_data);
  }
  if (status != NORMAL_MODE) {
    if (status == DOUBLE_QUOTE || status == SINGLE_QUOTE)
      throw_message_error("unexpected EOF while looking for matching", "\"",
                          true);
    throw_message_error("syntax error", "unexpected end of file", false);
    return (1);
  }
  return (0);
}
