/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skedikia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:30:46 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/04 14:32:13 by skedikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	add_new_env_variable(t_data *data, char *line)
{
	char	**new_env;
	int		size;
	int		i;

	if (!data || !line)
		return (EXIT_FAILURE);
	size = split_size(data->env) + 1;
	new_env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (ERROR_VALUE);
	i = 0;
	while (data->env[i])
	{
		new_env[i] = data->env[i];
		++i;
	}
	new_env[i] = line;
	new_env[i + 1] = NULL;
	free(data->env);
	data->env = new_env;
	return (EXIT_SUCCESS);
}

int	add_new_export_variable(t_data *data, char *line)
{
	char	**new_export;
	int		size;
	int		i;

	if (!data || !line)
		return (EXIT_FAILURE);
	size = split_size(data->export) + 1;
	new_export = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_export)
		return (ERROR_VALUE);
	i = 0;
	while (data->export[i])
	{
		new_export[i] = data->export[i];
		++i;
	}
	new_export[i] = line;
	new_export[i + 1] = NULL;
	free(data->export);
	data->export = new_export;
	data_sort_export(data);
	return (EXIT_SUCCESS);
}

int	update_env_variables(t_data *data, char *key, char *value, char *line)
{
	int	pos;

	if (!data || !key)
		return (EXIT_FAILURE);
	if (!value || !line)
		return (EXIT_SUCCESS);
	pos = find_env_variable_position(data->env, key);
	if (pos == NOT_FOUND)
		return (add_new_env_variable(data, line));
	free(data->env[pos]);
	data->env[pos] = line;
	return (EXIT_SUCCESS);
}

int	update_export_variables(t_data *data, char *key, char *value, char *line)
{
	int	pos;

	if (!data || !key || !line)
		return (EXIT_FAILURE);
	pos = find_export_variable_position(data->export, key);
	if (pos == NOT_FOUND)
		return (add_new_export_variable(data, line));
	if (!value)
		return (EXIT_SUCCESS);
	free(data->export[pos]);
	data->export[pos] = line;
	return (EXIT_SUCCESS);
}
