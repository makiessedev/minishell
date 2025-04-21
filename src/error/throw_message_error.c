/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_message_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:54:42 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 20:23:44 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	throw_message_error(char *errmsg, char *detail, int quotes)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	msg = join_strs(msg, errmsg);
	if (quotes)
		msg = join_strs(msg, " `");
	else
		msg = join_strs(msg, ": ");
	msg = join_strs(msg, detail);
	if (quotes)
		msg = join_strs(msg, "'");
	ft_putendl_fd(msg, STDERR_FILENO);
	erase_pointer(msg);
}
