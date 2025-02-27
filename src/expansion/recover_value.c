#include "minishell.h"

static int	var_exists(t_main *main_data, char *var)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (main_data->env[i])
	{
		if (ft_strncmp(main_data->env[i], var, len) == 0)
			return (0);
		i++;
	}
	return (1);
}

static char	*search_env_var(t_main *main_data, char *var)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (main_data->env[i])
	{
		if (ft_strncmp(main_data->env[i], var, len) == 0)
			break ;
		i++;
	}
	str = ft_strdup(main_data->env[i] + len);
	return (str);
}

char	*recover_val(t_token *token, char *str, t_main *main_data)
{
	char	*value;
	char	*var;

	var = identify_var(str);
	if (var && var_exists(main_data, var) == 0)
	{
		if (token != NULL)
			token->var_exists = true;
		value = search_env_var(main_data, var);
	}
	else if (var && var[0] == '?' && var[1] == '=')
		value = ft_itoa(g_exit_code);
	else
		value = NULL;
	erase_pointer(var);
	return (value);
}
