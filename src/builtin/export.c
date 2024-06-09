/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skedikia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:00:03 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/04 14:27:33 by skedikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	add_to_enviroment(t_data *data, char *key, char *value)
{
	char	*new_env_var;
	char	*new_export_var;
	int		status;

	if (!data)
		return (EXIT_FAILURE);
	new_env_var = create_env_variable(key, value);
	new_export_var = create_export_variable(key, value);
	if (!new_export_var)
	{
		free(new_env_var);
		return (ERROR_VALUE);
	}
	status = update_env_variables(data, key, value, new_env_var);
	status = update_export_variables(data, key, value, new_export_var);
	return (status);
}

static int	export_variable(t_data *data, char *arg)
{
	char	*key;
	char	*value;
	int		status;

	if (!data || !arg)
		return (EXIT_FAILURE);
	key = separate_key(arg);
	if (!key)
	{
		minishell_error("export", arg, "Variable Exporting error\n");
		return (ERROR_VALUE);
	}
	value = separate_value(arg);
	status = add_to_enviroment(data, key, value);
	free(key);
	free(value);
	if (status != EXIT_SUCCESS)
		minishell_error("export", arg, "Variable Exporting error\n");
	return (status);
}

static int	builtin_export_no_args(char **export)
{
	int	i;

	if (!export)
		return (EXIT_SUCCESS);
	i = 0;
	while (export[i])
	{
		printf("%s\n", export[i]);
		++i;
	}
	return (EXIT_SUCCESS);
}

int	builtin_export(t_data *data)
{
	int	i;
	int	status;

	if (!data)
	{
		minishell_error("export", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	status = EXIT_SUCCESS;
	i = 1;
	if (data->commands->args && data->commands->args[i])
	{
		while (data->commands->args[i])
		{
			if (builtin_export_validation(data->commands->args[i])
				== EXIT_FAILURE)
				status = EXIT_FAILURE;
			else
				status = export_variable(data, data->commands->args[i]);
			++i;
		}
	}
	else
		status = builtin_export_no_args(data->export);
	return (status);
}
