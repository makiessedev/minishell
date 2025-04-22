/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _commands_header.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:52:45 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 22:17:07 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _COMMANDS_HEADER_H
# define _COMMANDS_HEADER_H

int		exec_cd(t_main *main_data, char **args);
int		exec_echo(t_main *main_data, char **args);
int		exec_env(t_main *main_data, char **args);
int		exec_exit(t_main *main_data, char **args);
int		exec_export(t_main *main_data, char **args);
int		exec_pwd(t_main *main_data, char **args);
int		exec_unset(t_main *main_data, char **args);
int		change_dir(t_main *main_data, char *path);
void	update_wds(t_main *main_data, char *wd);
int		is_n_flag(char *arg);
void	echo_print_args(char **args, int n_flag, int i);
int		check_out_of_range(int neg, unsigned long long num, int *error);
int		ft_atoi_long(const char *str, int *error);
int		get_exit_code(char *arg, int *error);
int		is_quiet_mode(t_main *main_data);
char	**get_key_value_pair(char *arg);
#endif
