#include "minishell.h"
#include <stdlib.h>

int run_builtin(t_main *main_data, t_command *cmd) {
  int ret;

  ret = CMD_NOT_FOUND;
  if (ft_strncmp(cmd->command, "cd", 3) == 0)
    ret = exec_cd(main_data, cmd->args);
  else if (ft_strncmp(cmd->command, "echo", 5) == 0)
    ret = exec_echo(main_data, cmd->args);
  else if (ft_strncmp(cmd->command, "env", 4) == 0)
    ret = exec_env(main_data, cmd->args);
  else if (ft_strncmp(cmd->command, "export", 7) == 0)
    ret = exec_export(main_data, cmd->args);
  else if (ft_strncmp(cmd->command, "pwd", 4) == 0)
    ret = exec_pwd(main_data, cmd->args);
  else if (ft_strncmp(cmd->command, "unset", 6) == 0)
    ret = exec_unset(main_data, cmd->args);
  else if (ft_strncmp(cmd->command, "exit", 5) == 0)
    ret = exec_exit(main_data, cmd->args);
  return (ret);
}

static int run_sys_bin(t_main *main_data, t_command *cmd) {
  if (!cmd->command || cmd->command[0] == '\0')
    return (CMD_NOT_FOUND);
  if (cmd_is_dir(cmd->command))
    return (CMD_NOT_FOUND);
  cmd->path = get_cmd_path(main_data, cmd->command);
  if (!cmd->path)
    return (CMD_NOT_FOUND);
  if (execve(cmd->path, cmd->args, main_data->env) == -1)
    throw_command_error("execve", NULL, "error on execve command",
                        EXIT_FAILURE);
  return (EXIT_FAILURE);
}

static int run_local_bin(t_main *main_data, t_command *cmd) {
  int ret;

  ret = check_command_not_found(main_data, cmd);
  if (ret != 0)
    return (ret);
  if (execve(cmd->command, cmd->args, main_data->env) == -1)
    return (throw_command_error("execve", NULL, "error on execve command",
                                EXIT_FAILURE));
  return (EXIT_FAILURE);
}

int run_command(t_main *main_data, t_command *cmd) {
  int ret;

  if (!cmd || !cmd->command)
    erase_and_exit_shell(
        main_data,
        throw_command_error("child", NULL, "parsing error: no command to run!",
                            EXIT_FAILURE));
  if (!check_infile_outfile(cmd->io_fds))
    erase_and_exit_shell(main_data, EXIT_FAILURE);
  connect_command_pipes(main_data->cmd, cmd);
  redirect_standard_streams(cmd->io_fds);
  close_fds(main_data->cmd, false);
  if (ft_strchr(cmd->command, '/') == NULL) {
    ret = run_builtin(main_data, cmd);
    if (ret != CMD_NOT_FOUND)
      erase_and_exit_shell(main_data, ret);
    ret = run_sys_bin(main_data, cmd);
    if (ret != CMD_NOT_FOUND)
      erase_and_exit_shell(main_data, ret);
  }
  ret = run_local_bin(main_data, cmd);
  erase_and_exit_shell(main_data, ret);
  return (ret);
}
