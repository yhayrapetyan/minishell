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

static int	hyphen_n_case(char *arg, int *is_new_line)
{
	int	i;

	if (!arg || !is_new_line)
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		++i;
	}
	*is_new_line = 0;
	return (1);
}

static void	echo_print(t_data *data, int *is_new_line)
{
	int	i;

	if (!data || !is_new_line)
		return ;
	i = 1;
	while (data->commands->args[i])
	{
		if (data->commands->args[i][0] != '-')
			break ;
		if (!hyphen_n_case(data->commands->args[i], is_new_line))
			break ;
		++i;
	}
	while (data->commands->args[i])
	{
		write(STDOUT_FILENO, data->commands->args[i],
			ft_strlen(data->commands->args[i]));
		if (data->commands->args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		++i;
	}
}

int	builtin_echo(t_data *data)
{
	int	is_new_line;

	if (!data)
	{
		minishell_error("echo", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	if (data->commands->args)
	{
		is_new_line = 1;
		echo_print(data, &is_new_line);
		if (is_new_line)
			write(STDOUT_FILENO, "\n", 1);
	}
	else
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}