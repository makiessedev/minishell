#include "minishell.h"

int	exec_pwd(t_main *main_data, char **args)
{
	char	buf[PATH_MAX];
	char	*cwd;

	(void)args;
	if (main_data->working_dir)
	{
		ft_putendl_fd(main_data->working_dir, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	cwd = getcwd(buf, PATH_MAX);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	throw_command_error("pwd", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}
