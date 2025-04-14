/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:53:38 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:57:55 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_unset(t_main *main_data, char **args) {
  int i;
  int idx;
  int ret;

  ret = EXIT_SUCCESS;
  i = 1;
  while (args[i]) {
    if (!validate_env_var_name(args[i]) || ft_strchr(args[i], '=') != NULL)
      ret = EXIT_FAILURE;
    else {
      idx = get_env_var_index(main_data->env, args[i]);
      if (idx != -1)
        remove_env_var(main_data, idx);
    }
    i++;
  }
  return (ret);
}
