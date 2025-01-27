#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#ifndef _STDBOOL_H_
#define _STDBOOL_H_
# define bool int
# define true 1
# define false 0
#endif

# ifndef PATH_SIZE
#  define PATH_SIZE (1024*4)
# endif

typedef struct s_minishell
{
    char	**envp;
}	t_minishell;

void	launch_executable(char *full_cmds);

#endif
