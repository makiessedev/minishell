/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redirections_header.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:55:20 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 22:05:27 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		restore_standard_streams(t_io_fds *io);
int		redirect_standard_streams(t_io_fds *io);
int		check_infile_outfile(t_io_fds *io);
void	close_unused_pipes(t_command *cmds, t_command *skip_cmd);
int		initialize_command_pipes(t_main *data);
int		connect_command_pipes(t_command *cmds, t_command *c);
