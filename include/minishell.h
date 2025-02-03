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
bool	parse_input_and_execute(t_minishell	minisheel_data);

#endif
