#ifndef STDBOOL_H_
#define STDBOOL_H_
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
    char   *current_workdir;
    char   *old_workdir;
    int     last_command_exit_code;
}	t_minishell;