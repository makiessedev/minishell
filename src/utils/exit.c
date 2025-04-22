/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:57:11 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 21:59:38 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	erase_and_exit_shell(t_main *main_data, int exno)
{
	if (main_data)
	{
		if (main_data->cmd && main_data->cmd->io_fds)
			close_fds(main_data->cmd, TRUE);
		erase_main_data(main_data, TRUE);
	}
	exit(exno);
}
