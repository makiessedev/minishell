bool	restore_io(t_io_fds *io);
bool	redirect_io(t_io_fds *io);
bool	check_infile_outfile(t_io_fds *io);
void	close_pipe_fds(t_command *cmds, t_command *skip_cmd);
bool	create_pipes(t_main *data);
bool	set_pipe_fds(t_command *cmds, t_command *c);