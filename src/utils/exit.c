#include "minishell.h"

void	exit_shell(t_minishell *data, int exno)
{
	if (data)
	{
		if (data->cmd && data->cmd->io_fds)
			close_fds(data->cmd, true);
		free_data(data, true);
	}
	exit(exno);
}
