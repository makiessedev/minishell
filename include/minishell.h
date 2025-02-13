#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include "macros_structs.h"
#include "environment.h"
#include "tokenization.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

// tem

# define PROMPT "\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002"
# define HEREDOC_NAME "/tmp/.minishell_heredoc_"

# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define SUCCESS 0
# define FAILURE 1

// fim-temp

void	launch_executable(char *full_cmds);
void	parse_input_and_execute(t_minishell	*minisheel_data);
void	free_ptr(void *ptr);
int set_status_quote(t_minishell *minisheel_data, int i, int user_input_status_quote);
int save_word_token(t_token **lst_token, t_minishell *data, int index, int user_input_start);
int save_separator_token(t_token **lst_token, t_minishell *data, int index, int token_type);
int get_separator_token(t_minishell *minishell_data, int i);
int save_token(t_minishell *minisheel_data, int user_input_start, int *i);
t_token	*new_token(char *token, char *backup_token, int token_type, int token_status);
void	add_token(t_token **lst, t_token *token);
void	delete_token(t_token *lst, void (*del)(void *));
void	clear_token(t_token **lst, void (*del)(void *));
int	execute(t_minishell *data);
int	check_command_not_found(t_minishell *data, t_command *cmd);
bool	cmd_is_dir(char *cmd);
int	execute_builtin(t_minishell *data, t_command *cmd);
int	execute_command(t_minishell *data, t_command *cmd);
char	*get_cmd_path(t_minishell *data, char *name);
void	close_pipe_fds(t_command *cmds, t_command *skip_cmd);
bool	create_pipes(t_minishell *data);
bool	set_pipe_fds(t_command *cmds, t_command *c);
bool	restore_io(t_io_fds *io);
bool	redirect_io(t_io_fds *io);
bool	check_infile_outfile(t_io_fds *io);
void	signal_reset_prompt(int signo);
void	set_signals_interactive(void);
void	signal_print_newline(int signal);
void	set_signals_noninteractive(void);
void	ignore_sigquit(void);
bool	set_env_var(t_minishell *data, char *key, char *value);
bool	remove_env_var(t_minishell *data, int idx);
int	env_var_count(char **env);
int	get_env_var_index(char **env, char *var);
char	*get_env_var_value(char **env, char *var);
bool	is_valid_env_var_key(char *var);
bool	is_var_compliant(char c);
int	var_length(char *str);
char	*identify_var(char *str);
int	count_len(char *str, int count, int i);
bool	quotes_in_string(char *str);
int	handle_quotes(t_minishell *data);
int	remove_quotes(t_token **token_node);
char	*replace_str_heredoc(char *str, char *var_value, int index);
int	replace_var(t_token **token_node, char *var_value, int index);
void	copy_var_value(char *new_str, char *var_value, int *j);
char	*get_new_token_string(char *oldstr, char *var_value,
  int newstr_size, int index);
int	var_expander(t_minishell *data, t_token **token_lst);
char	*var_expander_heredoc(t_minishell *data, char *str);
int	check_if_var(t_token **token_lst);
int	check_consecutives(t_token **token_lst);
bool	parse_user_input(t_minishell *data);
t_token	*insert_lst_between(t_token **head, t_token *to_del, t_token *insert);
t_token	*lst_new_token(char *str, char *str_backup, int type, int status);
void	lst_add_back_token(t_token **alst, t_token *new_node);
void	lstdelone_token(t_token *lst, void (*del)(void *));
void	lstclear_token(t_token **lst, void (*del)(void *));
int	save_separator(t_token **token_lst, char *str, int index, int type);
int	save_word(t_token **token_lst, char *str, int index, int start);
int	is_separator(char *str, int i);
int	set_status(int status, char *str, int i);
int	save_word_or_sep(int *i, char *str, int start, t_minishell *data);
int	tokenization(t_minishell *data, char *str);
void	lst_delone_cmd(t_command *lst, void (*del)(void *));
void	lst_clear_cmd(t_command **lst, void (*del)(void *));
t_command	*lst_new_cmd(bool value);
void	lst_add_back_cmd(t_command **alst, t_command *new_node);
t_command	*lst_last_cmd(t_command *cmd);
void	create_commands(t_minishell *data, t_token *token);
int	count_arguments(t_token *temp);
int	create_args_default_mode(t_token **token_node, t_command *last_cmd);
int	add_args_default_mode(t_token **token_node, t_command *last_cmd);
int	fill_args(t_token **token_node, t_command *last_cmd);
char	*join_vars(t_token **token_node);
int	count_args(t_token *temp);
char	**copy_in_new_tab(int len, char **new_tab,
  t_command *last_cmd, t_token *tmp);
void	remove_empty_var_args(t_token **tokens);
int	create_args_echo_mode(t_token **token_node, t_command *last_cmd);
int	add_args_echo_mode(t_token **token_node, t_command *last_cmd);
void	parse_append(t_command **last_cmd, t_token **token_lst);
bool	fill_heredoc(t_minishell *data, t_io_fds *io, int fd);
bool	get_heredoc(t_minishell *data, t_io_fds *io);
void	parse_heredoc(t_minishell *data, t_command **last_cmd, t_token **token_lst);
bool	remove_old_file_ref(t_io_fds *io, bool infile);
void	parse_input(t_command **last_cmd, t_token **token_lst);
void	parse_pipe(t_command **cmd, t_token **token_lst);
char	*get_relative_path(char *file_to_open);
void	parse_trunc(t_command **last_cmd, t_token **token_lst);
void	parse_word(t_command **cmd, t_token **token_lst);
int	cd_builtin(t_minishell *data, char **args);
int	echo_builtin(t_minishell *data, char **args);
int	env_builtin(t_minishell *data, char **args);
int	exit_builtin(t_minishell *data, char **args);
int	export_builtin(t_minishell *data, char **args);
int	pwd_builtin(t_minishell *data, char **args);
int	unset_builtin(t_minishell *data, char **args);
void	free_data(t_minishell *data, bool clear_history);
void	close_fds(t_command *cmds, bool close_backups);
void	free_str_tab(char **tab);
void	free_ptr(void *ptr);
char	*join_strs(char *str, char *add);
int	errmsg_cmd(char *command, char *detail, char *error_message, int error_nb);
void	errmsg(char *errmsg, char *detail, int quotes);
bool	usage_message(bool return_val);
void	exit_shell(t_minishell *data, int exno);
bool	init_minishell(t_minishell *data, char **env);
void	init_io(t_command *cmd);
char	*recover_val(t_token *token, char *str, t_minishell *data);
int	ft_isspace(int c);
int	ft_strcmp(const char *s1, const char *s2);
void	free_io(t_io_fds *io);

#endif
