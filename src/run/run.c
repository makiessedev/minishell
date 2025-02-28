#include "minishell.h"

int	g_exit_code;

static int	get_children(t_main *main_data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_fds(main_data->cmd, false);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == main_data->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

static int	create_children(t_main *main_data)
{
	t_command	*cmd;

	cmd = main_data->cmd;
	while (main_data->pid != 0 && cmd)
	{
		main_data->pid = fork();
		if (main_data->pid == -1)
			return (throw_command_error("fork", NULL, strerror(errno), EXIT_FAILURE));
		else if (main_data->pid == 0)
			run_command(main_data, cmd);
		cmd = cmd->next;
	}
	return (get_children(main_data));
}

static int	prep_for_exec(t_main *main_data)
{
	if (!main_data || !main_data->cmd)
		return (EXIT_SUCCESS);
	if (!main_data->cmd->command)
	{
		if (main_data->cmd->io_fds
			&& !check_infile_outfile(main_data->cmd->io_fds))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(main_data))
		return (EXIT_FAILURE);
	return (CMD_NOT_FOUND);
}

int	run(t_main *main_data)
{
	int	ret;

	ret = prep_for_exec(main_data);
	if (ret != CMD_NOT_FOUND)
		return (ret);
	if (!main_data->cmd->pipe_output && !main_data->cmd->prev
		&& check_infile_outfile(main_data->cmd->io_fds))
	{
		redirect_io(main_data->cmd->io_fds);
		ret = run_builtin(main_data, main_data->cmd);
		restore_io(main_data->cmd->io_fds);
	}
	if (ret != CMD_NOT_FOUND)
		return (ret);
	return (create_children(main_data));
}
