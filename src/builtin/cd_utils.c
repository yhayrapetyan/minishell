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