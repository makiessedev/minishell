#include "minishell.h"

static void	update_wds(t_main *main_data, char *wd)
{
	set_env_var(main_data, "OLDPWD", get_env_var_value(main_data->env, "PWD"));
	set_env_var(main_data, "PWD", wd);
	if (main_data->old_working_dir)
	{
		free_ptr(main_data->old_working_dir);
		main_data->old_working_dir = ft_strdup(main_data->working_dir);
	}
	if (main_data->working_dir)
	{
		free_ptr(main_data->working_dir);
		main_data->working_dir = ft_strdup(wd);
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

static bool	change_dir(t_main *main_data, char *path)
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
		ret = ft_strjoin(main_data->working_dir, "/");
		tmp = ret;
		ret = ft_strjoin(tmp, path);
		free_ptr(tmp);
	}
	else
		ret = ft_strdup(cwd);
	update_wds(main_data, ret);
	return (true);
}

int	cd_builtin(t_main *main_data, char **args)
{
	char	*path;

	if (!args || !args[1] || ft_isspace(args[1][0])
		|| args[1][0] == '\0')
	{
		path = get_env_var_value(main_data->env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (errmsg_cmd("cd", NULL, "HOME not set", EXIT_FAILURE));
		return (!change_dir(main_data, path));
	}
	if (args[2])
		return (errmsg_cmd("cd", NULL, "too many arguments", EXIT_FAILURE));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_var_value(main_data->env, "OLDPWD");
		if (!path)
			return (errmsg_cmd("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		return (!change_dir(main_data, path));
	}
	return (!change_dir(main_data, args[1]));
}
