/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skedikia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:51:58 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/04 13:52:44 by skedikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	has_n_option(t_data *data)
{
	int	i;

	if (data->commands->args)
	{
		if (data->commands->args[0])
		{
			if (data->commands->args[1])
			{
				if (data->commands->args[1][0] == '-')
				{
					if (data->commands->args[1][1] == 'n')
					{
						i = 1;
						while (data->commands->args[1][++i])
						{
							if (data->commands->args[1][i] != 'n')
								return (NOT_FOUND);
						}
						return (EXIT_SUCCESS);
					}
				}
			}
		}
	}
	return (NOT_FOUND);
}

static void	print_echo(t_data *data, int start)
{
	int	i;

	if (!data)
		return ;
	i = start;
	while (data->commands->args[i])
	{
		write(STDOUT_FILENO, data->commands->args[i],
			ft_strlen(data->commands->args[i]));
//		if (data->commands->args[i + 1])
//			write(STDOUT_FILENO, " ", 1);
		++i;
	}
}
int	builtin_echo(t_data *data)
{
	if (!data)
	{
		minishell_error("echo", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	if (data->commands->args)
	{
		if (has_n_option(data) != NOT_FOUND)
			print_echo(data, 2);
		else
		{
			print_echo(data, 1);
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	else
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
