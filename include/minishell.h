#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include "macros.h"
#include "environment.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>



typedef struct s_minishell
{
    char	**envp;
    char   *current_workdir;
    char   *old_workdir;
}	t_minishell;

void	launch_executable(char *full_cmds);

#endif
