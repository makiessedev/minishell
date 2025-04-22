/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _expansion_header.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:54:52 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 22:14:08 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _EXPANSION_HEADER_H
# define _EXPANSION_HEADER_H

int		var_length(char *str);
char	*identify_var(char *str);
char	*resolve_variable_value(t_token *token, char *str, t_main *data);
int		process_variable_replacement(t_token **token_node, char *var_value,
			int index);
char	*replace_variable_in_heredoc(char *str, char *var_value, int index);
void	copy_var_value(char *new_str, char *var_value, int *j);
char	*get_new_token_string(char *oldstr, char *var_value, int newstr_size,
			int index);
int		expand_variables(t_main *data, t_token **token_lst);
char	*expand_variables_in_heredoc(t_main *data, char *str);
void	toggle_quote_mode(t_token **token_node, char c);
int		is_separator(char c);
int		is_var_enclosed_in_quotes(char *str, int i);
char	*replace_variable(t_token **token_node, char *str, char *var_value,
			int index);
int		remove_variable(t_token **token_node, char *str, int index);
#endif
