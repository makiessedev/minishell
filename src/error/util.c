/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:54:47 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:58:20 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *join_strs(char *str, char *add) {
  char *tmp;

  if (!add)
    return (str);
  if (!str)
    return (ft_strdup(add));
  tmp = str;
  str = ft_strjoin(tmp, add);
  erase_pointer(tmp);
  return (str);
}
