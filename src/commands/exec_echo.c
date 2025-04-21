/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:52:59 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 20:20:09 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_echo(t_main *main_data, char **args)
{
	int		i;
	bool	n_flag;

	(void)main_data;
	n_flag = false;
	i = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		n_flag = true;
		i++;
	}
	echo_print_args(args, n_flag, i);
	return (EXIT_SUCCESS);
}
