/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:52:59 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 22:15:15 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_echo(t_main *main_data, char **args)
{
	int	i;
	int	n_flag;

	(void)main_data;
	n_flag = FALSE;
	i = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		n_flag = TRUE;
		i++;
	}
	echo_print_args(args, n_flag, i);
	return (EXIT_SUCCESS);
}
