#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include "macros_structs.h"
#include "environment.h"
#include "tokenization.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

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

#endif
