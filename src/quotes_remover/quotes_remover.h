int	remove_quotes(t_token **token_node);
int	process_and_remove_quotes(t_main *main_data);
bool	contains_quotes(char *str);
int	calculate_length_without_quotes(char *str, int count, int i);
void	set_quote_mode(t_token **token_node, int *i);
bool	is_quotes_and_normal_mode(t_token **token_node, int i);
bool	reset_to_normal_mode(t_token **token_node, int *i);