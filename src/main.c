#include "minishell.h"

static bool setup_workdir(t_minishell *minishell_data)
{
	char buffer[PATH_SIZE];
	char *cwd;
	cwd = getcwd(buffer, PATH_SIZE);
	if (cwd == NULL)
		return (ft_putstr_fd("minishell: getcwd failed\n", 2), false);
	minishell_data->current_workdir = ft_strdup(cwd);
	if (is_existing_var("OLDPWD", minishell_data->envp))
	{
		minishell_data->old_workdir = get_var_value("OLDPWD", minishell_data->envp);
		if (!minishell_data->old_workdir)
			return (ft_putstr_fd("minishell: get_var_value failed\n", 2), false);
	}
	else
	{
		minishell_data->old_workdir = ft_strdup(minishell_data->current_workdir);
		if (!minishell_data->old_workdir)
			return (ft_putstr_fd("minishell: ft_strdup failed\n", 2), false);
	}
	return (true);
}

static bool init_setup(t_minishell *minishell_data, char **envp)
{
	minishell_data->envp = envp;
	if (!setup_workdir(minishell_data))
		return (false);
	return (true);
}

int		main(int ac, char **av, char **envp)
{
	char		*line;
	t_minishell	minisheel_data;

	if (ac != 1 || av[1])
	{
		ft_putstr_fd("minishell: No arguments are allowed\n", 2);
		return (1);
	}
	init_setup(&minisheel_data, envp);

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