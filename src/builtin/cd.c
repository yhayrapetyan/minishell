/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skedikia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:42:13 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/04 13:45:16 by skedikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_cd(t_data *data)
{
	int	status;

	if (!data)
	{
		minishell_error("cd", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	if (builtin_cd_validation(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!data->commands->args)
		status = change_directory(data, NULL);
	else
		status = change_directory(data, data->commands->args[1]);
	if (status == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (cd_update_env_values(data) == EXIT_FAILURE
		|| cd_update_export_values(data) == EXIT_FAILURE)
	{
		minishell_error("cd", NULL, "Data update error\n");
		return (EXIT_FAILURE);
	}
	return (status);
}
