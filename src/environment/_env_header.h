bool	update_or_create_env_variable(t_main *main_data, char *key, char *value);
bool	remove_env_var(t_main *main_data, int idx);
int	count_env_vars(char **env);
int	get_env_var_index(char **env, char *var);
char	*get_env_var_value(char **env, char *var);
bool	validate_env_var_name(char *var);
