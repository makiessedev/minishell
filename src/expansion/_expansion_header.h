bool	is_var_compliant(char c);
int	var_length(char *str);
char	*identify_var(char *str);
int	count_len(char *str, int count, int i);
bool	quotes_in_string(char *str);
int	handle_quotes(t_main *data);
int	remove_quotes(t_token **token_node);
char	*recover_val(t_token *token, char *str, t_main *data);
int	replace_var(t_token **token_node, char *var_value, int index);
char	*replace_str_heredoc(char *str, char *var_value, int index);
void	copy_var_value(char *new_str, char *var_value, int *j);
char	*get_new_token_string(char *oldstr, char *var_value,
int newstr_size, int index);
int	expand_variables(t_main *data, t_token **token_lst);
char	*expand_variables_in_heredoc(t_main *data, char *str);