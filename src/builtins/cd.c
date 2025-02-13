#include "minishell.h"

static void	update_wds(t_minishell *data, char *wd)
{
	set_env_var(data, "OLDPWD", get_env_var_value(data->envp, "PWD"));
	set_env_var(data, "PWD", wd);
	if (data->old_workdir)
	{
		free_ptr(data->old_workdir);
		data->old_workdir = ft_strdup(data->current_workdir);
	}
	if (data->current_workdir)
	{
		free_ptr(data->current_workdir);
		data->current_workdir = ft_strdup(wd);
	}
	free_ptr(wd);
}

static	bool	chdir_errno_mod(char *path)
{
	if (errno == ESTALE)
		errno = ENOENT;
	errmsg_cmd("cd", path, strerror(errno), errno);
	return (false);
}

static bool	change_dir(t_minishell *data, char *path)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];

	ret = NULL;
	if (chdir(path) != 0)
		return (chdir_errno_mod(path));
	ret = getcwd(cwd, PATH_MAX);
	if (!ret)
	{
		errmsg_cmd("cd: error retrieving current directory",
			"getcwd: cannot access parent directories",
			strerror(errno), errno);
		ret = ft_strjoin(data->current_workdir, "/");
		tmp = ret;
		ret = ft_strjoin(tmp, path);
		free_ptr(tmp);
	}
	else
		ret = ft_strdup(cwd);
	update_wds(data, ret);
	return (true);
}

int	cd_builtin(t_minishell *data, char **args)
{
	char	*path;

	if (!args || !args[1] || ft_isspace(args[1][0])
		|| args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 0)
	{
		path = get_env_var_value(data->envp, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (errmsg_cmd("cd", NULL, "HOME not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	if (args[2])
		return (errmsg_cmd("cd", NULL, "too many arguments", EXIT_FAILURE));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_var_value(data->envp, "OLDPWD");
		if (!path)
			return (errmsg_cmd("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	return (!change_dir(data, args[1]));
}
