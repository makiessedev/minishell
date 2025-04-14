/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _run_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:56:22 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:58:59 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int run_builtin(t_main *main_data, t_command *cmd);
int run_command(t_main *main_data, t_command *cmd);
bool cmd_is_dir(char *cmd);
int check_command_not_found(t_main *main_data, t_command *cmd);
int run(t_main *main_data);
char *get_cmd_path(t_main *main_data, char *name);
