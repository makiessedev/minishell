/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:52:49 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:57:39 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_cd(t_main *main_data, char **args) {
  char *path;

  if (!args || !args[1] || ft_isspace(args[1][0]) || args[1][0] == '\0') {
    path = get_env_var_value(main_data->env, "HOME");
    if (!path || *path == '\0' || ft_isspace(*path))
      return (throw_command_error("cd", NULL, "HOME not set", EXIT_FAILURE));
    return (!change_dir(main_data, path));
  }
  if (args[2])
    return (
        throw_command_error("cd", NULL, "too many arguments", EXIT_FAILURE));
  if (ft_strncmp(args[1], "-", 2) == 0) {
    path = get_env_var_value(main_data->env, "OLDPWD");
    if (!path)
      return (throw_command_error("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
    return (!change_dir(main_data, path));
  }
  return (!change_dir(main_data, args[1]));
}
