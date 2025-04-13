#include "minishell.h"

int throw_command_error(char *command, char *detail, char *error_message,
                        int error_nb) {
  char *msg;

  msg = ft_strdup("minishell: ");
  if (command != NULL) {
    msg = join_strs(msg, command);
    msg = join_strs(msg, ": ");
  }
  if (detail != NULL)
    msg = join_strs(msg, ": ");
  msg = join_strs(msg, error_message);
  ft_putendl_fd(msg, STDERR_FILENO);
  erase_pointer(msg);
  return (error_nb);
}
