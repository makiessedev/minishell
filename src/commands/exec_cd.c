#include "minishell.h"

static void update_wds(t_main *main_data, char *wd) {
  set_env_var(main_data, "OLDPWD", get_env_var_value(main_data->env, "PWD"));
  set_env_var(main_data, "PWD", wd);
  if (main_data->old_working_dir) {
    erase_pointer(main_data->old_working_dir);
    main_data->old_working_dir = ft_strdup(main_data->working_dir);
  }
  if (main_data->working_dir) {
    erase_pointer(main_data->working_dir);
    main_data->working_dir = ft_strdup(wd);
  }
  erase_pointer(wd);
}

static bool chdir_errno_mod(char *path) {
  if (errno == ESTALE)
    errno = ENOENT;
  throw_command_error("cd", path, strerror(errno), errno);
  return (false);
}

static bool change_dir(t_main *main_data, char *path) {
  char *ret;
  char *tmp;
  char cwd[PATH_MAX];

  ret = NULL;
  if (chdir(path) != 0)
    return (chdir_errno_mod(path));
  ret = getcwd(cwd, PATH_MAX);
  if (!ret) {
    ret = ft_strjoin(main_data->working_dir, "/");
    tmp = ret;
    ret = ft_strjoin(tmp, path);
    erase_pointer(tmp);
  } else
    ret = ft_strdup(cwd);
  update_wds(main_data, ret);
  return (true);
}

int exec_cd(t_main *main_data, char **args) {
  char *path;

  if (!args || !args[1] || ft_isspace(args[1][0]) || args[1][0] == '\0') {
    path = get_env_var_value(main_data->env, "HOME");
    if (!path || *path == '\0' || ft_isspace(*path))
      return (throw_command_error("cd", NULL, "HOME not set", EXIT_FAILURE));
    return (!change_dir(main_data, path));
  }
  if (args[2])
    return (
        throw_command_error("cd", NULL, "too many arguments", EXIT_FAILURE));
  if (ft_strncmp(args[1], "-", 2) == 0) {
    path = get_env_var_value(main_data->env, "OLDPWD");
    if (!path)
      return (throw_command_error("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
    return (!change_dir(main_data, path));
  }
  return (!change_dir(main_data, args[1]));
}
