bool	restore_standard_streams(t_io_fds *io);
bool	redirect_standard_streams(t_io_fds *io);
bool	check_infile_outfile(t_io_fds *io);
void	close_unused_pipes(t_command *cmds, t_command *skip_cmd);
bool	initialize_command_pipes(t_main *data);
bool	connect_command_pipes(t_command *cmds, t_command *c);
