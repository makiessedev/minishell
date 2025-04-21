/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:57:11 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:59:22 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	erase_and_exit_shell(t_main *main_data, int exno)
{
	if (main_data)
	{
		if (main_data->cmd && main_data->cmd->io_fds)
			close_fds(main_data->cmd, true);
		erase_main_data(main_data, true);
	}
	exit(exno);
}
