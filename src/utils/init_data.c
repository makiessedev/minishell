#include "minishell.h"

static bool	init_env(t_main *main_data, char **env)
{
	int		i;

	main_data->env = ft_calloc(env_var_count(env) + 1, sizeof(main_data->env));
	if (!main_data->env)
		return (false);
	i = 0;
	while (env[i])
	{
		main_data->env[i] = ft_strdup(env[i]);
		if (!main_data->env[i])
			return (false);
		i++;
	}
	return (true);
}

static bool	init_wds(t_main *main_data)
{
	char	buff[PATH_MAX];
	char	*wd;

	wd = getcwd(buff, PATH_MAX);
	main_data->working_dir = ft_strdup(wd);
	if (!main_data->working_dir)
		return (false);
	if (get_env_var_index(main_data->env, "OLDPWD") != -1)
	{
		main_data->old_working_dir = ft_strdup(get_env_var_value(main_data->env,
					"OLDPWD"));
		if (!main_data->old_working_dir)
			return (false);
	}
	else
	{
		main_data->old_working_dir = ft_strdup(wd);
		if (!main_data->old_working_dir)
			return (false);
	}
	return (true);
}

bool	init_data(t_main *main_data, char **env)
{
	bool is_seted_end;

	is_seted_end = init_env(main_data, env);
	if (!is_seted_end)
	{
		throw_command_error("Fatal", NULL, "Could not initialize environment", 1);
		return (false);
	}
	if (!init_wds(main_data))
	{
		throw_command_error("Fatal", NULL, "Could not initialize working directories",
			1);
		return (false);
	}
	main_data->token = NULL;
	main_data->user_input = NULL;
	main_data->cmd = NULL;
	main_data->pid = -1;
	g_exit_code = 0;
	return (true);
}

void	init_io(t_command *cmd)
{
	if (!cmd->io_fds)
	{
		cmd->io_fds = malloc(sizeof * cmd->io_fds);
		if (!cmd->io_fds)
			return ;
		cmd->io_fds->infile = NULL;
		cmd->io_fds->outfile = NULL;
		cmd->io_fds->heredoc_delimiter = NULL;
		cmd->io_fds->heredoc_quotes = false;
		cmd->io_fds->fd_in = -1;
		cmd->io_fds->fd_out = -1;
		cmd->io_fds->stdin_backup = -1;
		cmd->io_fds->stdout_backup = -1;
	}
}
