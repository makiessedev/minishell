/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_input_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:54:17 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 20:21:35 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	erase_input_output(t_io_fds *io)
{
	if (!io)
		return ;
	restore_standard_streams(io);
	if (io->heredoc_delimiter)
	{
		unlink(io->infile);
		erase_pointer(io->heredoc_delimiter);
	}
	if (io->infile)
		erase_pointer(io->infile);
	if (io->outfile)
		erase_pointer(io->outfile);
	if (io)
		erase_pointer(io);
}
