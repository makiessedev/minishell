/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_configs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:57:17 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/22 07:25:50 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int start_env(t_main *main_data, char **env) {
  int i;

  main_data->env = ft_calloc(count_env_vars(env) + 1, sizeof(main_data->env));
  if (!main_data->env)
    return (FALSE);
  i = 0;
  while (env[i]) {
    main_data->env[i] = ft_strdup(env[i]);
    if (!main_data->env[i])
      return (FALSE);
    i++;
  }
  return (TRUE);
}

static int init_wds(t_main *main_data) {
  char buff[PATH_MAX];
  char *wd;

  wd = getcwd(buff, PATH_MAX);
  main_data->working_dir = ft_strdup(wd);
  if (!main_data->working_dir)
    return (FALSE);
  if (get_env_var_index(main_data->env, "OLDPWD") != -1) {
    main_data->old_working_dir =
        ft_strdup(get_env_var_value(main_data->env, "OLDPWD"));
    if (!main_data->old_working_dir)
      return (FALSE);
  } else {
    main_data->old_working_dir = ft_strdup(wd);
    if (!main_data->old_working_dir)
      return (FALSE);
  }
  return (TRUE);
}

int init_data(t_main *main_data, char **env) {
  int is_seted_end;

  is_seted_end = start_env(main_data, env);
  if (!is_seted_end) {
    throw_command_error("Fatal", NULL, "Could not initialize environment", 1);
    return (FALSE);
  }
  if (!init_wds(main_data)) {
    throw_command_error("Fatal", NULL,
                        "Could not initialize working directories", 1);
    return (FALSE);
  }
  main_data->token = NULL;
  main_data->user_input = NULL;
  main_data->cmd = NULL;
  main_data->pid = -1;
  g_exit_code = 0;
  return (TRUE);
}

void init_io(t_command *cmd) {
  if (!cmd->io_fds) {
    cmd->io_fds = malloc(sizeof *cmd->io_fds);
    if (!cmd->io_fds)
      return;
    cmd->io_fds->infile = NULL;
    cmd->io_fds->outfile = NULL;
    cmd->io_fds->heredoc_delimiter = NULL;
    cmd->io_fds->heredoc_quotes = FALSE;
    cmd->io_fds->fd_in = -1;
    cmd->io_fds->fd_out = -1;
    cmd->io_fds->stdin_backup = -1;
    cmd->io_fds->stdout_backup = -1;
  }
}
