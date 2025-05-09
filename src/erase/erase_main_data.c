/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_main_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:54:21 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 22:05:26 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	erase_main_data(t_main *main_data, int clear_history)
{
	if (main_data && main_data->user_input)
	{
		erase_pointer(main_data->user_input);
		main_data->user_input = NULL;
	}
	if (main_data && main_data->token)
		lstclear_token(&main_data->token, &erase_pointer);
	if (main_data && main_data->cmd)
		lst_clear_cmd(&main_data->cmd, &erase_pointer);
	if (clear_history == TRUE)
	{
		if (main_data && main_data->working_dir)
			erase_pointer(main_data->working_dir);
		if (main_data && main_data->old_working_dir)
			erase_pointer(main_data->old_working_dir);
		if (main_data && main_data->env)
			erase_tab_string(main_data->env);
		rl_clear_history();
	}
}
