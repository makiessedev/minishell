#include "minishell.h"

static int	env_variable_exists(t_main *main_data, char *var)
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

static char	*get_env_variable_value(t_main *main_data, char *var)
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

char	*resolve_variable_value(t_token *token, char *str, t_main *main_data)
{
	char	*value;
	char	*var;

	var = identify_var(str);
	if (var && env_variable_exists(main_data, var) == 0)
	{
		if (token != NULL)
			token->var_exists = true;
		value = get_env_variable_value(main_data, var);
	}
	else if (var && var[0] == '?' && var[1] == '=')
		value = ft_itoa(g_exit_code);
	else
		value = NULL;
	erase_pointer(var);
	return (value);
}


int	process_variable_replacement(t_token **token_node, char *var_value, int index)
{
	if (var_value == NULL)
	{
		if (remove_variable(token_node, (*token_node)->token, index) == 1)
		{
			erase_pointer(var_value);
			return (1);
		}
	}
	else
	{
		if (replace_variable(token_node, (*token_node)->token, var_value, index) == NULL)
		{
			erase_pointer(var_value);
			return (1);
		}
	}
	erase_pointer(var_value);
	return (0);
}

char	*replace_variable_in_heredoc(char *str, char *var_value, int index)
{
	char	*tmp;

	tmp = NULL;
	if (var_value == NULL)
		*str = '\0';
	else
	{
		tmp = str;
		str = replace_variable(NULL, str, var_value, index);
		erase_pointer(tmp);
	}
	erase_pointer(var_value);
	return (str);
}
