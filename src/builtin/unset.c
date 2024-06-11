/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:30:14 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/11 14:23:41 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	move_split_elements_except_one(char **split_1,
		char **split_2, int pos)
{
	int	i;
	int	j;

	if (!split_1 || !split_2)
		return ;
	i = 0;
	j = 0;
	while (split_2[j])
	{
		if (j == pos)
		{
			++j;
			if (split_2[j] == NULL)
				break ;
		}
		split_1[i] = split_2[j];
		++j;
		++i;
	}
	split_1[i] = NULL;
}

static int	delete_from_export(t_data *data, char *arg)
{
	int		pos;
	char	**new_export;

	if (!data)
		return (EXIT_FAILURE);
	if (!arg)
		return (EXIT_SUCCESS);
	pos = find_export_variable_position(data->export, arg);
	if (pos == NOT_FOUND)
		return (EXIT_SUCCESS);
	new_export = (char **)malloc(sizeof(char *) * (split_size(data->export)));
	if (!new_export)
		return (EXIT_FAILURE);
	move_split_elements_except_one(new_export, data->export, pos);
	free(data->export[pos]);
	free(data->export);
	data->export = new_export;
	return (EXIT_SUCCESS);
}

static int	delete_from_env(t_data *data, char *arg)
{
	int		pos;
	char	**new_env;

	if (!data)
		return (EXIT_FAILURE);
	if (!arg)
		return (EXIT_SUCCESS);
	pos = find_env_variable_position(data->env, arg);
	if (pos == NOT_FOUND)
		return (EXIT_SUCCESS);
	new_env = (char **)malloc(sizeof(char *) * (split_size(data->env)));
	if (!new_env)
		return (ERROR_VALUE);
	move_split_elements_except_one(new_env, data->env, pos);
	free(data->env[pos]);
	free(data->env);
	data->env = new_env;
	return (EXIT_SUCCESS);
}

int	delete_variable(t_data *data, char *arg)
{
	int	status;

	if (!data)
		return (EXIT_FAILURE);
	if (!arg)
		return (EXIT_SUCCESS);
	status = delete_from_env(data, arg);
	if (status != EXIT_SUCCESS)
	{
		minishell_error("unset", "NULL", "env delete error\n");
		return (status);
	}
	status = delete_from_export(data, arg);
	if (status != EXIT_SUCCESS)
	{
		minishell_error("unset", "NULL", "export delete error\n");
		return (status);
	}
	if (find_export_variable_position(data->export, "PWD") == NOT_FOUND)
		data->is_pwd_unset_for_cd = 1;
	return (EXIT_SUCCESS);
}

int	builtin_unset(t_data *data)
{
	int	i;
	int	status;

	status = 0;
	if (!data)
	{
		minishell_error("unset", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	if (!data->commands->args)
		return (EXIT_SUCCESS);
	i = 1;
	while (data->commands->args[i])
	{
		status = delete_variable(data, data->commands->args[i]);
		++i;
	}
	return (status);
}
