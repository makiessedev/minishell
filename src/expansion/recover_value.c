#include "minishell.h"

static int	var_exists(t_minishell *data, char *var)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], var, len) == 0)
			return (0);
		i++;
	}
	return (1);
}

static char	*search_env_var(t_minishell *data, char *var)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], var, len) == 0)
			break ;
		i++;
	}
	str = ft_strdup(data->envp[i] + len);
	return (str);
}

char	*recover_val(t_token *token, char *str, t_minishell *data)
{
	char	*value;
	char	*var;

	var = identify_var(str);
	if (var && var_exists(data, var) == 0)
	{
		if (token != NULL)
			token->var_exists = true;
		value = search_env_var(data, var);
	}
	else if (var && var[0] == '?' && var[1] == '=')
		value = ft_itoa(data->last_command_exit_code);
	else
		value = NULL;
	free_ptr(var);
	return (value);
}
