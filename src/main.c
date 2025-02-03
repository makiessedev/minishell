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
	t_minishell	minisheel_data;

	if (ac != 1 || av[1])
	{
		ft_putstr_fd("minishell: No arguments are allowed\n", 2);
		return (1);
	}
	if (!init_setup(&minisheel_data, envp))
		return (1);

	while (1)
	{
		minisheel_data.input_user = readline("minishell$ ");
		if (!minisheel_data.input_user || is_only_space(minisheel_data.input_user))
			continue ; // review this in the future and free minishell_data to prevent leaks
		if (minisheel_data.input_user[0] != '\0')
			add_history(input_user);
		parse_input_and_execute(&minisheel_data);
		free(input_user); // review later
	}
	return (0);
}