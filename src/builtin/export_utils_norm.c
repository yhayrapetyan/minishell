/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_norm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skedikia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:33:24 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/04 14:33:25 by skedikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*create_env_variable(char *key, char *value)
{
	char	*env_var;
	char	*temp;

	if (!key || !value)
		return (NULL);
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	env_var = ft_strjoin(temp, value);
	free(temp);
	return (env_var);
}

char	*create_export_variable(char *key, char *value)
{
	char	*export_var;
	char	*temp;

	if (!key)
		return (NULL);
	temp = ft_strjoin("declare -x ", key);
	if (!value)
		return (temp);
	export_var = ft_strjoin(temp, "=\"");
	free(temp);
	if (!export_var)
		return (NULL);
	temp = ft_strjoin(export_var, value);
	free(export_var);
	if (!temp)
		return (NULL);
	export_var = ft_strjoin(temp, "\"");
	free(temp);
	return (export_var);
}
