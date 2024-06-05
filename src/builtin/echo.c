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

int	builtin_echo(t_data *data)
{
	int	i;

	if (!data)
	{
		minishell_error("echo", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	if (data->commands->args)
	{
		i = 1;
		while (data->commands->args[i])
		{
			write(STDOUT_FILENO, data->commands->args[i],
				ft_strlen(data->commands->args[i]));
			if (data->commands->args[i + 1])
				write(STDOUT_FILENO, " ", 1);
			++i;
		}
	}
	write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
