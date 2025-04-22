/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _run_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:56:22 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 22:15:02 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RUN_HEADER_H
# define _RUN_HEADER_H

int		run_builtin(t_main *main_data, t_command *cmd);
int		run_command(t_main *main_data, t_command *cmd);
int		cmd_is_dir(char *cmd);
int		check_command_not_found(t_main *main_data, t_command *cmd);
int		run(t_main *main_data);
char	*get_cmd_path(t_main *main_data, char *name);
void	set_break(int sig);
#endif
