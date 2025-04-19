/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:53:54 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/19 22:18:10 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **resize_environment_buffer(t_main *main_data, int size) {
  char **new_env;
  int i;

  new_env = ft_calloc(size + 1, sizeof *new_env);
  if (!new_env)
    return (NULL);
  i = 0;
  while (main_data->env[i] && i < size) {
    new_env[i] = ft_strdup(main_data->env[i]);
    erase_pointer(main_data->env[i]);
    i++;
  }
  free(main_data->env);
  return (new_env);
}

bool update_or_create_env_variable(t_main *main_data, char *key, char *value)
{
  int idx;
  char *tmp;

  idx = get_env_var_index(main_data->env, key);
  if (value == NULL)
    value = "";
  tmp = ft_strjoin("=", value);
  if (!tmp)
    return (false);
  if (idx != -1 && main_data->env[idx]) {
    erase_pointer(main_data->env[idx]);
    main_data->env[idx] = ft_strjoin(key, tmp);
  } else {
    idx = count_env_vars(main_data->env);
    main_data->env = resize_environment_buffer(main_data, idx + 1);
    if (!main_data->env)
      return (false);
    main_data->env[idx] = ft_strjoin(key, tmp);
  }
  erase_pointer(tmp);
  return (true);
}

bool remove_env_var(t_main *main_data, int idx) {
  int i;
  int count;

  if (idx > count_env_vars(main_data->env))
    return (false);
  erase_pointer(main_data->env[idx]);
  i = idx;
  count = idx;
  while (main_data->env[i + 1]) {
    main_data->env[i] = ft_strdup(main_data->env[i + 1]);
    erase_pointer(main_data->env[i + 1]);
    count++;
    i++;
  }
  main_data->env = resize_environment_buffer(main_data, count);
  if (!main_data->env)
    return (false);
  return (true);
}
