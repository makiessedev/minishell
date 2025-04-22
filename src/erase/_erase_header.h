/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _erase_header.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:54:01 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 22:05:26 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ERASE_HEADER_H
# define _ERASE_HEADER_H

void	erase_main_data(t_main *main_data, int clear_history);
void	close_fds(t_command *cmds, int close_backups);
void	erase_input_output(t_io_fds *io);
void	erase_main_data(t_main *main_data, int clear_history);
void	erase_pointer(void *ptr);
void	erase_tab_string(char **tab);
void	lst_delone_cmd(t_command *lst, void (*del)(void *));
void	lst_clear_cmd(t_command **lst, void (*del)(void *));
#endif