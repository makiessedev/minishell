bool	set_env_var(t_main *main_data, char *key, char *value);
bool	remove_env_var(t_main *main_data, int idx);
int	env_var_count(char **env);
int	get_env_var_index(char **env, char *var);
char	*get_env_var_value(char **env, char *var);
bool	is_valid_env_var_key(char *var);