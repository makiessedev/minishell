#include "minishell.h"

void	exit_shell(t_main *main_data, int exno)
{
	if (main_data)
	{
		if (main_data->cmd && main_data->cmd->io_fds)
			close_fds(main_data->cmd, true);
		free_data(main_data, true);
	}
	exit(exno);
}
