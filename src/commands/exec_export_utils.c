#include "minishell.h"

char **get_key_value_pair(char *arg) {
  char **tmp;
  char *eq_pos;

  eq_pos = ft_strchr(arg, '=');
  tmp = malloc(sizeof *tmp * (2 + 1));
  tmp[0] = ft_substr(arg, 0, eq_pos - arg);
  tmp[1] = ft_substr(eq_pos, 1, ft_strlen(eq_pos));
  tmp[2] = NULL;
  return (tmp);
}
