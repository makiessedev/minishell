/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:52:54 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 22:05:26 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_wds(t_main *main_data, char *wd)
{
	update_or_create_env_variable(main_data, "OLDPWD",
		get_env_var_value(main_data->env, "PWD"));
	update_or_create_env_variable(main_data, "PWD", wd);
	if (main_data->old_working_dir)
	{
		erase_pointer(main_data->old_working_dir);
		main_data->old_working_dir = ft_strdup(main_data->working_dir);
	}
	if (main_data->working_dir)
	{
		erase_pointer(main_data->working_dir);
		main_data->working_dir = ft_strdup(wd);
	}
	erase_pointer(wd);
}

int	change_dir(t_main *main_data, char *path)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];

	ret = NULL;
	if (chdir(path) != 0)
	{
		throw_command_error("cd", path, "chdir error", CHDIR_ERROR);
		return (FALSE);
	}
	ret = getcwd(cwd, PATH_MAX);
	if (!ret)
	{
		ret = ft_strjoin(main_data->working_dir, "/");
		tmp = ret;
		ret = ft_strjoin(tmp, path);
		erase_pointer(tmp);
	}
	else
		ret = ft_strdup(cwd);
	update_wds(main_data, ret);
	return (TRUE);
}
