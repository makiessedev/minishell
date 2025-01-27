#include "minishell.h"

bool is_existing_var(char *var, char **envp)
{
	if (get_var_index(var, envp) == -1)
		return (false);
	return (true);
}