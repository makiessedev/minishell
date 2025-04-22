/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remover.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:56:14 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 22:05:27 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		remove_quotes(t_token **token_node);
int		process_and_remove_quotes(t_main *main_data);
int		contains_quotes(char *str);
int		calculate_length_without_quotes(char *str, int count, int i);
void	set_quote_mode(t_token **token_node, int *i);
int		is_quotes_and_normal_mode(t_token **token_node, int i);
int		reset_to_normal_mode(t_token **token_node, int *i);
