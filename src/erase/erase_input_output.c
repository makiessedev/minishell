#include "minishell.h"

void	erase_input_output(t_io_fds *io)
{
	if (!io)
		return ;
	restore_standard_streams(io);
	if (io->heredoc_delimiter)
	{
		unlink(io->infile);
		erase_pointer(io->heredoc_delimiter);
	}
	if (io->infile)
		erase_pointer(io->infile);
	if (io->outfile)
		erase_pointer(io->outfile);
	if (io)
		erase_pointer(io);
}
