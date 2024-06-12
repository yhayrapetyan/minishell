/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_norm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skedikia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:41:58 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/04 13:42:00 by skedikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env_variable_position(char **env, char *key)
{
	int	i;
	int	key_len;

	if (!env || !key)
		return (NOT_FOUND);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0)
		{
			if (env[i][key_len] == '=')
				return (i);
		}
		++i;
	}
	return (NOT_FOUND);
}

int	find_export_variable_position(char **export, char *key)
{
	int	i;
	int	key_len;
	int	declare_x_len;

	if (!export || !key)
		return (NOT_FOUND);
	key_len = ft_strlen(key);
	declare_x_len = ft_strlen("declare -x ");
	i = 0;
	while (export[i])
	{
		if (ft_strncmp(export[i] + declare_x_len, key, key_len) == 0)
		{
			if (export[i][declare_x_len + key_len] == '=' ||
					export[i][declare_x_len + key_len] == '\0')
				return (i);
		}
		++i;
	}
	return (NOT_FOUND);
}
