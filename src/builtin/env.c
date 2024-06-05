/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skedikia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:33:39 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/04 14:34:20 by skedikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_env(t_data *data)
{
	int	i;

	if (!data)
	{
		minishell_error("env", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	if (!data->env)
	{
		minishell_error("env", NULL, "No such file or directory\n");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (data->env[i])
	{
		if (ft_strchr(data->env[i], '=') != NULL)
		{
			write(STDOUT_FILENO, data->env[i], ft_strlen(data->env[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}
