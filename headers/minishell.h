#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"
# include "structs_macros.h"

# include "../src/builtins/_builtins_header.h"
# include "../src/env/_env_header.h"
# include "../src/execution/_execution_header.h"
# include "../src/expansion/_expansion_header.h"
# include "../src/lexer/_lexer_header.h"
# include "../src/parser/_parser_header.h"
# include "../src/redirections/_redirections_header.h"
# include "../src/utils/_utils_header.h"


extern int	g_last_exit_code;

void	bootstrap(t_main *main_data);
void	signals_manager(void);

#endif

