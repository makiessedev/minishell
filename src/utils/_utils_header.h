/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils_header.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:57:07 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:59:20 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	erase_and_exit_shell(t_main *main_data, int exno);
int		ft_isspace(int c);
bool	init_data(t_main *main_data, char **env);
void	init_io(t_command *cmd);
