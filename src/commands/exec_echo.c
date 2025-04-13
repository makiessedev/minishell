#include "minishell.h"

int exec_echo(t_main *main_data, char **args) {
  int i;
  bool n_flag;

  (void)main_data;
  n_flag = false;
  i = 1;
  while (args[i] && is_n_flag(args[i])) {
    n_flag = true;
    i++;
  }
  echo_print_args(args, n_flag, i);
  return (EXIT_SUCCESS);
}
