/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:53:25 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:57:51 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_key_value_pair(char *arg) {
  char **tmp;
  char *eq_pos;

  eq_pos = ft_strchr(arg, '=');
  tmp = malloc(sizeof *tmp * (2 + 1));
  tmp[0] = ft_substr(arg, 0, eq_pos - arg);
  tmp[1] = ft_substr(eq_pos, 1, ft_strlen(eq_pos));
  tmp[2] = NULL;
  return (tmp);
}
