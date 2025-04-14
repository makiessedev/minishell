/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _error_header.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:54:35 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:58:14 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *join_strs(char *str, char *add);
int throw_command_error(char *command, char *detail, char *error_message,
                        int error_nb);
void throw_message_error(char *errmsg, char *detail, int quotes);
