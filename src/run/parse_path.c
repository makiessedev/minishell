/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:56:25 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:59:01 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *find_valid_cmd_path(char *cmd, char **paths) {
  int i;
  char *cmd_path;

  cmd_path = NULL;
  i = 0;
  while (paths[i]) {
    cmd_path = ft_strjoin(paths[i], cmd);
    if (!cmd_path) {
      throw_command_error("malloc", NULL, "an unexpected error occured",
                          EXIT_FAILURE);
      return (NULL);
    }
    if (access(cmd_path, F_OK | X_OK) == 0)
      return (cmd_path);
    erase_pointer(cmd_path);
    i++;
  }
  return (NULL);
}

static char **get_paths_from_env(t_main *main_data) {
  char **env_paths;

  if (get_env_var_index(main_data->env, "PATH") == -1)
    return (NULL);
  env_paths = ft_split(get_env_var_value(main_data->env, "PATH"), ':');
  if (!env_paths)
    return (NULL);
  return (env_paths);
}

char *get_cmd_path(t_main *main_data, char *name) {
  char **env_paths;
  char *cmd;
  char *cmd_path;

  if (!name)
    return (NULL);
  env_paths = get_paths_from_env(main_data);
  if (!env_paths)
    return (NULL);
  cmd = ft_strjoin("/", name);
  if (!cmd) {
    erase_tab_string(env_paths);
    return (NULL);
  }
  cmd_path = find_valid_cmd_path(cmd, env_paths);
  if (!cmd_path) {
    erase_pointer(cmd);
    erase_tab_string(env_paths);
    return (NULL);
  }
  return (cmd_path);
}
