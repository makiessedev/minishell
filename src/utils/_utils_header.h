/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils_header.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:57:07 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/26 20:57:37 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _UTILS_HEADER_H
#define _UTILS_HEADER_H

void erase_and_exit_shell(t_main *main_data, int exno);
int ft_isspace(int c);
int init_data(t_main *main_data, char **env);
void init_io(t_command *cmd);
int count_tab(char **tab);
#endif
