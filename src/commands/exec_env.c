/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:53:08 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 20:20:14 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_env(t_main *main_data, char **args)
{
	int	i;

	if (args && args[1])
		return (throw_command_error("env", NULL, "too many arguments", 2));
	i = 0;
	if (!main_data->env)
		return (EXIT_FAILURE);
	while (main_data->env[i])
		ft_putendl_fd(main_data->env[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
