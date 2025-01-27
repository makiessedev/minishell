#include "minishell.h"

static int get_var_index(char *var, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static bool is_existing_var(char *var, char **envp)
{
	if (get_var_index(var, envp) == -1)
		return (false);
	return (true);
}

static char *get_var_value(char *var, char **envp)
{
	int	index;
	char	*value;

	index = get_var_index(var, envp);
	if (index == -1)
		return (NULL);
	value = ft_strchr(envp[index], '=') + 1;
	return (value);
}

static bool setup_workdir(t_minishell *minishell_data)
{
	char buffer[PATH_SIZE];
	cwd = getcwd(buffer, PATH_SIZE);
	if (cwd == NULL)
		return (ft_putstr_fd("minishell: getcwd failed\n"), false);
	minishell_data->current_workdir = ft_strdup(cwd);
	if (is_existing_var("OLDPWD", minishell_data->envp))
	{
		minishell_data->old_workdir = get_var_value("OLDPWD", minishell_data->envp);
		if (!minishell_data->old_workdir)
			return (ft_putstr_fd("minishell: get_var_value failed\n"), false);
	}
	else
	{
		minishell_data->old_workdir = ft_strdup(minishell_data->current_workdir);
		if (!minishell_data->old_workdir)
			return (ft_putstr_fd("minishell: ft_strdup failed\n"), false);
	}
	return (true);
}

static bool init_setup(t_minishell *minishell_data, char **envp)
{
	minishell_data->envp = envp;
	if (!setup_workdir(minishell_data->current_workdir))
		return (false);
	return (true);
}

int		main(int ac, char **av, char **envp)
{
	char		*line;
	t_minishell	*minisheel_data;

	if (ac != 1)
	{
		ft_putstr_fd("minishell: No arguments are allowed\n");
		return (1);
	}
	init_setup(minisheel_data, envp);

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (line[0] != '\0')
			add_history(line);
		launch_executable(line);
		free(line);
	}
	return (0);
}