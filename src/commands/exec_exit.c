/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:53:14 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 22:17:11 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exit_code(char **args, int *error)
{
	int	exit_code;

	if (!args || !args[1])
		return (g_exit_code);
	exit_code = get_exit_code(args[1], error);
	if (*error)
		return (throw_command_error("exit", args[1],
				"numeric argument required", 2));
	if (args[2])
		return (throw_command_error("exit", NULL, "too many arguments", 1));
	return (exit_code);
}

static void	update_shell_level(t_main *main_data)
{
	int		shell_level;
	char	*new_lvl;

	shell_level = ft_atoi(getenv("SHLVL"));
	if (shell_level == 1)
		return ;
	new_lvl = ft_itoa(--shell_level);
	if (new_lvl)
		update_or_create_env_variable(main_data, "SHLVL", new_lvl);
	free(new_lvl);
}

int	exec_exit(t_main *main_data, char **args)
{
	int	exit_code;
	int	error;
	int	quiet;

	error = FALSE;
	quiet = is_quiet_mode(main_data);
	if (!quiet)
		ft_putendl_fd("exit", 2);
	exit_code = handle_exit_code(args, &error);
	if (error && args[2])
		return (exit_code);
	update_shell_level(main_data);
	erase_and_exit_shell(main_data, exit_code);
	return (2);
}
