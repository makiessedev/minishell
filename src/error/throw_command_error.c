/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_command_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:54:38 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 20:21:57 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	throw_command_error(char *command, char *detail, char *error_message,
		int error_nb)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	if (command != NULL)
	{
		msg = join_strs(msg, command);
		msg = join_strs(msg, ": ");
	}
	if (detail != NULL)
		msg = join_strs(msg, ": ");
	msg = join_strs(msg, error_message);
	ft_putendl_fd(msg, STDERR_FILENO);
	erase_pointer(msg);
	return (error_nb);
}
