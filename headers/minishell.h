#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
#include "structs_macros.h"

# include "libft.h"

extern int	g_last_exit_code;

bool		init_data(t_data *data, char **env);
void		init_io(t_command *cmd);
void		exit_shell(t_data *data, int exno);
int			errmsg_cmd(char *command, char *detail, char *error_message,
				int error_nb);
void		errmsg(char *errmsg, char *detail, int quotes);
bool		usage_message(bool return_val);
void		free_data(t_data *data, bool clear_history);
void		close_fds(t_command *cmds, bool close_backups);
void		free_io(t_io_fds *io);
void		free_ptr(void *ptr);
void		free_str_tab(char **tab);
bool		parse_user_input(t_data *data);
int			tokenization(t_data *data, char *str);
int			save_word_or_sep(int *i, char *str, int start, t_data *data);
int			set_status(int status, char *str, int i);
int			is_separator(char *str, int i);
int			save_word(t_token **token_lst, char *str, int index, int start);
int			save_separator(t_token **token_lst, char *str, int index, int type);
int			check_consecutives(t_token **token_lst);
int			check_if_var(t_token **token_lst);
t_token		*lst_new_token(char *str, char *str_backup, int type, int status);
void		lst_add_back_token(t_token **alst, t_token *new_node);
void		lstdelone_token(t_token *lst, void (*del)(void *));
void		lstclear_token(t_token **lst, void (*del)(void *));
t_token		*insert_lst_between(t_token **head, t_token *to_del,
				t_token *insert);
int			var_expander(t_data *data, t_token **token_lst);
char		*recover_val(t_token *token, char *str, t_data *data);
char		*identify_var(char *str);
int			var_length(char *str);
bool		is_var_compliant(char c);
int			replace_var(t_token **token_node, char *var_value, int index);
void		copy_var_value(char *new_str, char *var_value, int *j);
char		*var_expander_heredoc(t_data *data, char *str);
char		*replace_str_heredoc(char *str, char *var_value, int index);
void		copy_var_value(char *new_str, char *var_value, int *j);
char		*get_new_token_string(char *oldstr, char *var_value,
				int newstr_size, int index);
int			handle_quotes(t_data *data);
bool		quotes_in_string(char *str);
int			count_len(char *str, int count, int i);
int			remove_quotes(t_token **token_node);
void		create_commands(t_data *data, t_token *token);
void		parse_word(t_command **cmd, t_token **token_lst);
int			fill_args(t_token	**token_node, t_command *last_cmd);
int			add_args_default_mode(t_token **token_node, t_command *last_cmd);
int			create_args_default_mode(t_token **token_node, t_command *last_cmd);
int			add_args_echo_mode(t_token **token_node, t_command *last_cmd);
int			create_args_echo_mode(t_token **token_node, t_command *last_cmd);
char		*join_vars(t_token **token_node);
int			count_args(t_token *temp);
char		**copy_in_new_tab(int len, char **new_tab,
				t_command *last_cmd, t_token *tmp);
void		remove_empty_var_args(t_token **tokens);
t_command	*lst_new_cmd(bool value);
void		lst_add_back_cmd(t_command **alst, t_command *new_node);
t_command	*lst_last_cmd(t_command *cmd);
t_command	*lst_first_cmd(t_command *cmd);
void		lst_delone_cmd(t_command *lst, void (*del)(void *));
void		lst_clear_cmd(t_command **lst, void (*del)(void *));
void		parse_trunc(t_command **last_cmd, t_token **token_lst);
char		*get_relative_path(char *file_to_open);
bool		remove_old_file_ref(t_io_fds *io, bool infile);
void		parse_input(t_command **last_cmd, t_token **token_lst);
void		parse_append(t_command **last_cmd, t_token **token_lst);
void		parse_heredoc(t_data *data, t_command **last_cmd,
				t_token **token_lst);
bool		fill_heredoc(t_data *data, t_io_fds *io, int fd);
void		parse_pipe(t_command **cmd, t_token **token_lst);
int			env_var_count(char **env);
int			get_env_var_index(char **env, char *var);
char		*get_env_var_value(char **env, char *var);
bool		is_valid_env_var_key(char *var);
bool		set_env_var(t_data *data, char *key, char *value);
bool		remove_env_var(t_data *data, int idx);
int			env_builtin(t_data *data, char **args);
int			pwd_builtin(t_data *data, char **args);
int			echo_builtin(t_data *data, char **args);
int			export_builtin(t_data *data, char **args);
int			unset_builtin(t_data *data, char **args);
int			cd_builtin(t_data *data, char **args);
int			exit_builtin(t_data *data, char **args);
void		ignore_sigquit(void);
void		set_signals_interactive(void);
void		set_signals_noninteractive(void);
int			execute(t_data *data);
int			execute_command(t_data *data, t_command *cmd);
int			execute_builtin(t_data *data, t_command *cmd);
bool		cmd_is_dir(char *cmd);
int			check_command_not_found(t_data *data, t_command *cmd);
char		*get_cmd_path(t_data *data, char *cmd);
bool		create_pipes(t_data *data);
bool		set_pipe_fds(t_command *cmds, t_command *curr_cmd);
void		close_pipe_fds(t_command *cmds, t_command *skip_cmd);
bool		check_infile_outfile(t_io_fds *io);
bool		redirect_io(t_io_fds *io);
bool		restore_io(t_io_fds *io);
bool		get_heredoc(t_data *data, t_io_fds *io);
void		print_cmd_list(t_data *data);
void		print_token_list(t_token **tokens);
int	ft_isspace(int c);

#endif