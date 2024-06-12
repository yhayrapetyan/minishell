/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skedikia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:31:07 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/04 13:33:25 by skedikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	builtin_run_norm(t_data *data, int cmd_len)
{
	if (!data)
		return ;
	if (cmd_len == 3)
	{
		if (ft_strncmp(data->commands->name, "pwd", 3) == 0)
			g_exit_status = builtin_pwd(data);
		else if (ft_strncmp(data->commands->name, "env", 3) == 0)
			g_exit_status = builtin_env(data);
	}
	else if (cmd_len == 2)
	{
		if (ft_strncmp(data->commands->name, "cd", 2) == 0)
			g_exit_status = builtin_cd(data);
	}
}

int	builtin_run(t_data *data)
{
	int	cmd_len;

	if (!data)
		return (NOT_FOUND);
	cmd_len = ft_strlen(data->commands->name);
	if (cmd_len == 6)
	{
		if (ft_strncmp(data->commands->name, "export", 6) == 0)
			g_exit_status = builtin_export(data);
	}
	else if (cmd_len == 5)
	{
		if (ft_strncmp(data->commands->name, "unset", 5) == 0)
			g_exit_status = builtin_unset(data);
	}
	else if (cmd_len == 4)
	{
		if (ft_strncmp(data->commands->name, "echo", 4) == 0)
			g_exit_status = builtin_echo(data);
	}
	else if (cmd_len == 3 || cmd_len == 2)
		builtin_run_norm(data, cmd_len);
	else
		return (NOT_FOUND);
	return (EXIT_SUCCESS);
}
