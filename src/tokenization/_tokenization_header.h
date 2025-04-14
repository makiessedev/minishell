/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tokenization_header.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:56:43 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:59:09 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int validate_syntax_and_variables(t_token **token_lst);
bool process_user_command(t_main *data);
t_token *lst_new_token(char *str, char *str_backup, int type, int status);
void lst_add_back_token(t_token **alst, t_token *new_node);
void lstdelone_token(t_token *lst, void (*del)(void *));
void lstclear_token(t_token **lst, void (*del)(void *));
int get_type_separator_token(char *str, int i);
int storage_word_or_separator_token(int *i, int start, t_main *main_data);
int tokenization(t_main *main_data);
