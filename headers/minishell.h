#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include "structs_macros.h"
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "../src/commands/_commands_header.h"
#include "../src/env/_env_header.h"
#include "../src/erase/_erase_header.h"
#include "../src/error/_error_header.h"
#include "../src/expansion/_expansion_header.h"
#include "../src/parser/_parser_header.h"
#include "../src/quotes_remover/quotes_remover.h"
#include "../src/redirections/_redirections_header.h"
#include "../src/run/_run_header.h"
#include "../src/tokenization/_tokenization_header.h"
#include "../src/utils/_utils_header.h"

extern int g_exit_code;

void bootstrap(t_main *main_data);
void signals_manager(void);

#endif
