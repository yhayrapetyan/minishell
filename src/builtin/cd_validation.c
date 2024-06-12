/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_validation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skedikia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:48:11 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/04 13:48:58 by skedikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd_validation(t_data *data)
{
	if (!data)
	{
		minishell_error("cd", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	if (!data->commands->args)
		return (EXIT_SUCCESS);
	if (data->commands->args[0])
	{
		if (data->commands->args[1])
		{
			if (data->commands->args[2])
			{
				minishell_error("cd", NULL, "too many arguments");
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}
