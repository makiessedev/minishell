#include "minishell.h"

int exec_unset(t_main *main_data, char **args) {
  int i;
  int idx;
  int ret;

  ret = EXIT_SUCCESS;
  i = 1;
  while (args[i]) {
    if (!is_valid_env_var_key(args[i]) || ft_strchr(args[i], '=') != NULL)
      ret = EXIT_FAILURE;
    else {
      idx = get_env_var_index(main_data->env, args[i]);
      if (idx != -1)
        remove_env_var(main_data, idx);
    }
    i++;
  }
  return (ret);
}
