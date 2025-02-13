#include "minishell.h"

static bool	init_env(t_minishell *data, char **env)
{
	int		i;

	data->envp = ft_calloc(env_var_count(env) + 1, sizeof * data->envp);
	if (!data->envp)
		return (false);
	i = 0;
	while (env[i])
	{
		data->envp[i] = ft_strdup(env[i]);
		if (!data->envp[i])
			return (false);
		i++;
	}
	return (true);
}

static bool	init_wds(t_minishell *data)
{
	char	buff[PATH_MAX];
	char	*wd;

	wd = getcwd(buff, PATH_MAX);
	data->current_workdir = ft_strdup(wd);
	if (!data->current_workdir)
		return (false);
	if (get_env_var_index(data->envp, "OLDPWD") != -1)
	{
		data->old_workdir = ft_strdup(get_env_var_value(data->envp,
					"OLDPWD"));
		if (!data->old_workdir)
			return (false);
	}
	else
	{
		data->old_workdir = ft_strdup(wd);
		if (!data->old_workdir)
			return (false);
	}
	return (true);
}

bool	init_minishell(t_minishell *data, char **env)
{
	if (!init_env(data, env))
	{
		errmsg_cmd("Fatal", NULL, "Could not initialize environment", 1);
		return (false);
	}
	if (!init_wds(data))
	{
		errmsg_cmd("Fatal", NULL, "Could not initialize working directories",
			1);
		return (false);
	}
	data->token = NULL;
	data->input_user = NULL;
	data->cmd = NULL;
	data->pid = -1;
	data->last_command_exit_code = 0;
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
