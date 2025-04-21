/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redirections_header.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:55:20 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 20:23:08 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool	restore_standard_streams(t_io_fds *io);
bool	redirect_standard_streams(t_io_fds *io);
bool	check_infile_outfile(t_io_fds *io);
void	close_unused_pipes(t_command *cmds, t_command *skip_cmd);
bool	initialize_command_pipes(t_main *data);
bool	connect_command_pipes(t_command *cmds, t_command *c);
