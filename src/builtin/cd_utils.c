/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skedikia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:47:13 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/04 13:47:56 by skedikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*get_value_from_env(char **env, char *key)
{
	int	i;
	int	key_len;

	if (!env || !key)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0)
		{
			if (env[i][key_len] == '=')
				return (env[i] + ft_strlen(key) + 1);
		}
		++i;
	}
	return (NULL);
}

int	cd_update_workdirs(t_data *data, char *new_path)
{
	if (!data)
	{
		minishell_error("cd", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	free(data->old_work_dir);
	data->old_work_dir = data->work_dir;
	data->work_dir = ft_strdup(new_path);
	if (!data->work_dir)
	{
		minishell_error("cd", NULL, "Memory Allocation error\n");
		return (ERROR_VALUE);
	}
	return (EXIT_SUCCESS);
}

int	cd_update_export_values(t_data *data)
{
	char	*new_pwd;
	char	*new_oldpwd;
	int		pos;

	if (!data)
		return (EXIT_FAILURE);
	pos = find_export_variable_position(data->export, "PWD");
	if (pos != NOT_FOUND)
	{
		new_pwd = create_export_variable("PWD", data->work_dir);
		if (!new_pwd)
			return (EXIT_FAILURE);
		free(data->export[pos]);
		data->export[pos] = new_pwd;
	}
	pos = find_export_variable_position(data->export, "OLDPWD");
	if (pos != NOT_FOUND)
	{
		new_oldpwd = create_export_variable("OLDPWD", data->old_work_dir);
		if (!new_oldpwd)
			return (EXIT_FAILURE);
		free(data->export[pos]);
		data->export[pos] = new_oldpwd;
	}
	return (EXIT_SUCCESS);
}

int	cd_update_env_values(t_data *data)
{
	char	*new_pwd;
	char	*new_oldpwd;
	int		pos;

	if (!data)
		return (EXIT_FAILURE);
	pos = find_env_variable_position(data->env, "PWD");
	if (pos != NOT_FOUND)
	{
		new_pwd = create_env_variable("PWD", data->work_dir);
		if (!new_pwd)
			return (EXIT_FAILURE);
		free(data->env[pos]);
		data->env[pos] = new_pwd;
	}
	pos = find_env_variable_position(data->env, "OLDPWD");
	if (pos != NOT_FOUND)
	{
		new_oldpwd = create_env_variable("OLDPWD", data->old_work_dir);
		if (!new_oldpwd)
			return (EXIT_FAILURE);
		free(data->env[pos]);
		data->env[pos] = new_oldpwd;
	}
	return (EXIT_SUCCESS);
}
