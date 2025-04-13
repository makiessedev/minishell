#include "minishell.h"

bool is_n_flag(char *arg) {
  int i;
  bool n_flag;

  n_flag = false;
  i = 0;
  if (arg[i] != '-')
    return (n_flag);
  i++;
  while (arg[i] && arg[i] == 'n')
    i++;
  if (arg[i] == '\0')
    n_flag = true;
  return (n_flag);
}

void echo_print_args(char **args, bool n_flag, int i) {
  if (!args[i]) {
    if (!n_flag)
      ft_putchar_fd('\n', STDOUT_FILENO);
    return;
  }
  while (args[i]) {
    ft_putstr_fd(args[i], STDOUT_FILENO);
    if (args[i + 1])
      ft_putchar_fd(' ', STDOUT_FILENO);
    else if (!args[i + 1] && !n_flag)
      ft_putchar_fd('\n', STDOUT_FILENO);
    i++;
  }
}
