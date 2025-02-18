#include "minishell.h"

int	execute_builtin(t_main *main_data, t_command *cmd)
{
	int	ret;

	ret = CMD_NOT_FOUND;
	if (ft_strncmp(cmd->command, "cd", 3) == 0)
		ret = cd_builtin(main_data, cmd->args);
	else if (ft_strncmp(cmd->command, "echo", 5) == 0)
		ret = echo_builtin(main_data, cmd->args);
	else if (ft_strncmp(cmd->command, "env", 4) == 0)
		ret = env_builtin(main_data, cmd->args);
	else if (ft_strncmp(cmd->command, "export", 7) == 0)
		ret = export_builtin(main_data, cmd->args);
	else if (ft_strncmp(cmd->command, "pwd", 4) == 0)
		ret = pwd_builtin(main_data, cmd->args);
	else if (ft_strncmp(cmd->command, "unset", 6) == 0)
		ret = unset_builtin(main_data, cmd->args);
	else if (ft_strncmp(cmd->command, "exit", 5) == 0)
		ret = exit_builtin(main_data, cmd->args);
	return (ret);
}

static int	execute_sys_bin(t_main *main_data, t_command *cmd)
{
	if (!cmd->command || cmd->command[0] == '\0')
		return (CMD_NOT_FOUND);
	if (cmd_is_dir(cmd->command))
		return (CMD_NOT_FOUND);
	cmd->path = get_cmd_path(main_data, cmd->command);
	if (!cmd->path)
		return (CMD_NOT_FOUND);
	if (execve(cmd->path, cmd->args, main_data->env) == -1)
		errmsg_cmd("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

static int	execute_local_bin(t_main *main_data, t_command *cmd)
{
	int	ret;

	ret = check_command_not_found(main_data, cmd);
	if (ret != 0)
		return (ret);
	if (execve(cmd->command, cmd->args, main_data->env) == -1)
		return (errmsg_cmd("execve", NULL, strerror(errno), errno));
	return (EXIT_FAILURE);
}

int	execute_command(t_main *main_data, t_command *cmd)
{
	int	ret;

	if (!cmd || !cmd->command)
		exit_shell(main_data, errmsg_cmd("child", NULL,
				"parsing error: no command to execute!", EXIT_FAILURE));
	if (!check_infile_outfile(cmd->io_fds))
		exit_shell(main_data, EXIT_FAILURE);
	set_pipe_fds(main_data->cmd, cmd);
	redirect_io(cmd->io_fds);
	close_fds(main_data->cmd, false);
	if (ft_strchr(cmd->command, '/') == NULL)
	{
		ret = execute_builtin(main_data, cmd);
		if (ret != CMD_NOT_FOUND)
			exit_shell(main_data, ret);
		ret = execute_sys_bin(main_data, cmd);
		if (ret != CMD_NOT_FOUND)
			exit_shell(main_data, ret);
	}
	ret = execute_local_bin(main_data, cmd);
	exit_shell(main_data, ret);
	return (ret);
}
