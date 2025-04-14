/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _commands_header.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:52:45 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:57:35 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int exec_cd(t_main *main_data, char **args);
int exec_echo(t_main *main_data, char **args);
int exec_env(t_main *main_data, char **args);
int exec_exit(t_main *main_data, char **args);
int exec_export(t_main *main_data, char **args);
int exec_pwd(t_main *main_data, char **args);
int exec_unset(t_main *main_data, char **args);
bool change_dir(t_main *main_data, char *path);
void update_wds(t_main *main_data, char *wd);
bool is_n_flag(char *arg);
void echo_print_args(char **args, bool n_flag, int i);
bool check_out_of_range(int neg, unsigned long long num, bool *error);
int ft_atoi_long(const char *str, bool *error);
int get_exit_code(char *arg, bool *error);
bool is_quiet_mode(t_main *main_data);
char **get_key_value_pair(char *arg);
