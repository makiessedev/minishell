/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorais <makiesse.dev@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:53:46 by mmorais           #+#    #+#             */
/*   Updated: 2025/04/14 17:57:56 by mmorais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool update_or_create_env_variable(t_main *main_data, char *key, char *value);
bool remove_env_var(t_main *main_data, int idx);
int count_env_vars(char **env);
int get_env_var_index(char **env, char *var);
char *get_env_var_value(char **env, char *var);
bool validate_env_var_name(char *var);
