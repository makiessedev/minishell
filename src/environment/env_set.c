#include "minishell.h"

static char	**realloc_env_vars(t_minishell *data, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof * new_env);
	if (!new_env)
		return (NULL);
	i = 0;
	while (data->envp[i] && i < size)
	{
		new_env[i] = ft_strdup(data->envp[i]);
		free_ptr(data->envp[i]);
		i++;
	}
	free(data->envp);
	return (new_env);
}

bool	set_env_var(t_minishell *data, char *key, char *value)
{
	int		idx;
	char	*tmp;

	idx = get_env_var_index(data->envp, key);
	if (value == NULL)
		value = "";
	tmp = ft_strjoin("=", value);
	if (!tmp)
		return (false);
	if (idx != -1 && data->envp[idx])
	{
		free_ptr(data->envp[idx]);
		data->envp[idx] = ft_strjoin(key, tmp);
	}
	else
	{
		idx = env_var_count(data->envp);
		data->envp = realloc_env_vars(data, idx + 1);
		if (!data->envp)
			return (false);
		data->envp[idx] = ft_strjoin(key, tmp);
	}
	free_ptr(tmp);
	return (true);
}

bool	remove_env_var(t_minishell *data, int idx)
{
	int	i;
	int	count;

	if (idx > env_var_count(data->envp))
		return (false);
	free_ptr(data->envp[idx]);
	i = idx;
	count = idx;
	while (data->envp[i + 1])
	{
		data->envp[i] = ft_strdup(data->envp[i + 1]);
		free_ptr(data->envp[i + 1]);
		count++;
		i++;
	}
	data->envp = realloc_env_vars(data, count);
	if (!data->envp)
		return (false);
	return (true);
}
