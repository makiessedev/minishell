#include "minishell.h"

void	free_data(t_main *main_data, bool clear_history)
{
	if (main_data && main_data->user_input)
	{
		free_ptr(main_data->user_input);
		main_data->user_input = NULL;
	}
	if (main_data && main_data->token)
		lstclear_token(&main_data->token, &free_ptr);
	if (main_data && main_data->cmd)
		lst_clear_cmd(&main_data->cmd, &free_ptr);
	if (clear_history == true)
	{
		if (main_data && main_data->working_dir)
			free_ptr(main_data->working_dir);
		if (main_data && main_data->old_working_dir)
			free_ptr(main_data->old_working_dir);
		if (main_data && main_data->env)
			free_str_tab(main_data->env);
		rl_clear_history();
	}
}