/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:54:25 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:58:11 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void erase_pointer(void *ptr) {
  if (ptr != NULL) {
    free(ptr);
    ptr = NULL;
  }
}
