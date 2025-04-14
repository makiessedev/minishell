/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:55:09 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:58:30 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool is_valid_var(char c) {
  if (ft_isalnum(c) == 0 && c != '_')
    return (false);
  else
    return (true);
}

int var_length(char *str) {
  int i;
  int count;

  count = 0;
  i = 0;
  while (str[i] != '$')
    i++;
  i++;
  if ((str[i] >= '0' && str[i] <= '9') || str[i] == '?')
    return (count + 1);
  while (str[i]) {
    if (is_valid_var(str[i]) == false)
      break;
    count++;
    i++;
  }
  return (count);
}

char *identify_var(char *str) {
  char *var;
  char *tmp;
  int start;
  int len;
  int i;

  i = 0;
  start = 0;
  while (str[i]) {
    if (str[i] == '$') {
      start = i + 1;
      break;
    }
    i++;
  }
  len = var_length(str);
  var = ft_substr(str, start, len);
  if (!var)
    return (NULL);
  tmp = ft_strjoin(var, "=");
  erase_pointer(var);
  return (tmp);
}
