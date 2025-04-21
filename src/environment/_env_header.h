/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zombunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:53:46 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/21 22:14:49 by zombunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		update_or_create_env_variable(t_main *main_data, char *key,
			char *value);
int		remove_env_var(t_main *main_data, int idx);
int		count_env_vars(char **env);
int		get_env_var_index(char **env, char *var);
char	*get_env_var_value(char **env, char *var);
int		validate_env_var_name(char *var);
