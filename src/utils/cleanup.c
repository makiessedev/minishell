#include "minishell.h"

void	free_data(t_main *main_data, bool clear_history)
{
	if (main_data && main_data->user_input)
	{
		free_ptr(main_data->user_input);
		main_data->user_input = NULL;
	}
	if (main_data && main_data->token)
		lstclear_token(&main_data->token, &free_ptr);
	if (main_data && main_data->cmd)
		lst_clear_cmd(&main_data->cmd, &free_ptr);
	if (clear_history == true)
	{
		if (main_data && main_data->working_dir)
			free_ptr(main_data->working_dir);
		if (main_data && main_data->old_working_dir)
			free_ptr(main_data->old_working_dir);
		if (main_data && main_data->env)
			free_str_tab(main_data->env);
		rl_clear_history();
	}
}

void	close_fds(t_command *cmds, bool close_backups)
{
	if (cmds->io_fds)
	{
		if (cmds->io_fds->fd_in != -1)
			close(cmds->io_fds->fd_in);
		if (cmds->io_fds->fd_out != -1)
			close(cmds->io_fds->fd_out);
		if (close_backups)
			restore_io(cmds->io_fds);
	}
	close_pipe_fds(cmds, NULL);
}

void	free_io(t_io_fds *io)
{
	if (!io)
		return ;
	restore_io(io);
	if (io->heredoc_delimiter)
	{
		unlink(io->infile);
		free_ptr(io->heredoc_delimiter);
	}
	if (io->infile)
		free_ptr(io->infile);
	if (io->outfile)
		free_ptr(io->outfile);
	if (io)
		free_ptr(io);
}

void	free_str_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i])
			{
				free_ptr(tab[i]);
				tab[i] = NULL;
			}
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}
