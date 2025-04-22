/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _error_header.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:54:35 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 20:21:51 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ERROR_HEADER_H
# define _ERROR_HEADER_H

char	*join_strs(char *str, char *add);
int		throw_command_error(char *command, char *detail, char *error_message,
			int error_nb);
void	throw_message_error(char *errmsg, char *detail, int quotes);
#endif
