#include "minishell.h"

int exec_export(t_main *main_data, char **args) {
  int i;
  char **tmp;
  int ret;

  ret = EXIT_SUCCESS;
  i = 1;
  if (!args[i])
    return (exec_env(main_data, NULL));
  while (args[i]) {
    if (!validate_env_var_name(args[i])) {
      throw_command_error("export", args[i], "not a valid identifier", false);
      ret = EXIT_FAILURE;
    } else if (ft_strchr(args[i], '=') != NULL) {
      tmp = get_key_value_pair(args[i]);
      update_or_create_env_variable(main_data, tmp[0], tmp[1]);
      erase_tab_string(tmp);
    }
    i++;
  }
  return (ret);
}
