/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _erase_header.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:54:01 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:58:02 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void erase_main_data(t_main *main_data, bool clear_history);
void close_fds(t_command *cmds, bool close_backups);
void erase_input_output(t_io_fds *io);
void erase_main_data(t_main *main_data, bool clear_history);
void erase_pointer(void *ptr);
void erase_tab_string(char **tab);
void lst_delone_cmd(t_command *lst, void (*del)(void *));
void lst_clear_cmd(t_command **lst, void (*del)(void *));
