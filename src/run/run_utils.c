/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:56:39 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 22:05:26 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_is_dir(char *cmd)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}

void	set_break(int sig)
{
	char	*shell_level;

	(void)sig;
	shell_level = getenv("SHLVL");
	if (shell_level && ft_atoi(shell_level) >= 2)
		write("\n");
}

int	check_command_not_found(t_main *main_data, t_command *cmd)
{
	if (ft_strchr(cmd->command, '/') == NULL
		&& get_env_var_index(main_data->env, "PATH") != -1)
		return (throw_command_error(cmd->command, NULL, "command not found",
				CMD_NOT_FOUND));
	if (access(cmd->command, F_OK) != 0)
		return (throw_command_error(cmd->command, NULL,
				"error on try access command", CMD_NOT_FOUND));
	else if (cmd_is_dir(cmd->command))
		return (throw_command_error(cmd->command, NULL, "Is a directory",
				CMD_NOT_EXECUTABLE));
	else if (access(cmd->command, F_OK | X_OK) != 0)
		return (throw_command_error(cmd->command, NULL,
				"error on verify command", CMD_NOT_EXECUTABLE));
	return (EXIT_SUCCESS);
}
