int	execute_builtin(t_data *data, t_command *cmd);
int	execute_command(t_data *data, t_command *cmd);
bool	cmd_is_dir(char *cmd);
int	check_command_not_found(t_data *data, t_command *cmd);
int	execute(t_data *data);
char	*get_cmd_path(t_data *data, char *name);