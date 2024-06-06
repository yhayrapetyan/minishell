/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skedikia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:53:00 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/04 13:59:14 by skedikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	builtin_exit_norm(t_data *data)
{
	if (!data)
		return (EXIT_FAILURE);
	if (data->commands->args)
	{
		if (data->commands->args[0])
		{
			if (data->commands->args[1])
			{
				if (builtin_exit_validation(data->commands->args[1])
					!= EXIT_SUCCESS)
					return (NOT_NUMERIC_ERROR);
				if (data->commands->args[2])
				{
					write(STDOUT_FILENO, "exit\n", 5);
					minishell_error("exit", NULL, "too many arguments\n");
					return (EXIT_FAILURE);
				}
				g_exit_status = ft_atoi(data->commands->args[1])
					% CHAR_SIZE_COMBINATIONS;
			}
		}
	}
	return (EXIT_SUCCESS);
}

int	builtin_exit(t_data *data)
{
	int	status;

	if (!data)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		minishell_error("exit", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	if (!data->commands)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		exit(0);
	}
	status = builtin_exit_norm(data);
	if (status != EXIT_SUCCESS)
		return (status);
	write(STDOUT_FILENO, "exit\n", 5);
	exit(g_exit_status);
	return (EXIT_SUCCESS);
}
