/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remover.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:56:14 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:58:55 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int remove_quotes(t_token **token_node);
int process_and_remove_quotes(t_main *main_data);
bool contains_quotes(char *str);
int calculate_length_without_quotes(char *str, int count, int i);
void set_quote_mode(t_token **token_node, int *i);
bool is_quotes_and_normal_mode(t_token **token_node, int i);
bool reset_to_normal_mode(t_token **token_node, int *i);
