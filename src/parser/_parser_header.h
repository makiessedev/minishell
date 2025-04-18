/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parser_header.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:55:34 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:58:39 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_command *lst_new_cmd(bool value);
void lst_add_back_cmd(t_command **alst, t_command *new_node);
t_command *lst_last_cmd(t_command *cmd);
void create_commands(t_main *main_data, t_token *token);
int count_arguments(t_token *temp);
int create_args_default_mode(t_token **token_node, t_command *last_cmd);
int add_args_default_mode(t_token **token_node, t_command *last_cmd);
int populate_command_args(t_token **token_node, t_command *last_cmd);
int count_args(t_token *temp);
char **copy_in_new_tab(int len, char **new_tab, t_command *last_cmd,
                       t_token *tmp);
void remove_empty_variable_arguments(t_token **tokens);
int create_args_echo_mode(t_token **token_node, t_command *last_cmd);
int add_args_echo_mode(t_token **token_node, t_command *last_cmd);
void append_parser(t_command **last_cmd, t_token **token_lst);
bool fill_heredoc(t_main *main_data, t_io_fds *io, int fd);
bool get_heredoc(t_main *main_data, t_io_fds *io);
void parse_heredoc(t_main *main_data, t_command **last_cmd,
                   t_token **token_lst);
bool remove_old_file_ref(t_io_fds *io, bool infile);
void open_outfile_trunc(t_io_fds *io, char *file, char *var_filename);
void open_infile(t_io_fds *io, char *file, char *original_filename);
void open_outfile_append(t_io_fds *io, char *file, char *var_filename);

void input_parser(t_command **last_cmd, t_token **token_lst);
void pipe_parser(t_command **cmd, t_token **token_lst);
void redirect_parser(t_command **last_cmd, t_token **token_lst);
void word_parser(t_command **cmd, t_token **token_lst);
