#include "minishell.h"

void open_outfile_trunc(t_io_fds *io, char *file, char *var_filename) {
  if (!remove_old_file_ref(io, false))
    return;
  io->outfile = ft_strdup(file);
  if (io->outfile && io->outfile[0] == '\0') {
    throw_command_error(var_filename, NULL, "ambiguous redirect", false);
    return;
  }
  io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
  if (io->fd_out == -1)
    throw_command_error(io->outfile, NULL, "open failure", false);
}

bool remove_old_file_ref(t_io_fds *io, bool infile) {
  if (infile == true && io->infile) {
    if (io->fd_in == -1 || (io->outfile && io->fd_out == -1))
      return (false);
    if (io->heredoc_delimiter != NULL) {
      erase_pointer(io->heredoc_delimiter);
      io->heredoc_delimiter = NULL;
      unlink(io->infile);
    }
    erase_pointer(io->infile);
    close(io->fd_in);
  } else if (infile == false && io->outfile) {
    if (io->fd_out == -1 || (io->infile && io->fd_in == -1))
      return (false);
    erase_pointer(io->outfile);
    close(io->fd_out);
  }
  return (true);
}

void open_infile(t_io_fds *io, char *file, char *original_filename) {
  if (!remove_old_file_ref(io, true))
    return;
  io->infile = ft_strdup(file);
  if (io->infile && io->infile[0] == '\0') {
    throw_command_error(original_filename, NULL, "ambiguous redirect", false);
    return;
  }
  io->fd_in = open(io->infile, O_RDONLY);
  if (io->fd_in == -1)
    throw_command_error(io->infile, NULL, "open failure", false);
}

void open_outfile_append(t_io_fds *io, char *file, char *var_filename) {
  if (!remove_old_file_ref(io, false))
    return;
  io->outfile = ft_strdup(file);
  if (io->outfile && io->outfile[0] == '\0' && var_filename) {
    throw_command_error(var_filename, NULL, "ambiguous redirect", false);
    return;
  }
  io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
  if (io->fd_out == -1)
    throw_command_error(io->outfile, NULL, "open failure", false);
}
