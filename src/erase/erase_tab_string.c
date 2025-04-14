/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_tab_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:54:29 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:58:12 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void erase_tab_string(char **tab) {
  int i;

  i = 0;
  if (tab) {
    while (tab[i]) {
      if (tab[i]) {
        erase_pointer(tab[i]);
        tab[i] = NULL;
      }
      i++;
    }
    free(tab);
    tab = NULL;
  }
}
