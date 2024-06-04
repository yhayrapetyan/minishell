/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:08:06 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/30 20:08:06 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_exit_status(int err_type)
{
	if (err_type == -5)
		return (SYNTAX_STAT);
	else if (err_type == -6)
		return (AMBIGOUS_REDIR_STAT);
	else if (err_type == -7)
		return (FILE_OPEN_STAT);
	return (0);
}

/* idk how to name this function */
static void	exit_helper(char *cmd_name, char *err_message)
{
	char	*err_msg;

	err_msg = parse_err(cmd_name, err_message);
	if (!err_msg)
		exit (1);
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
	free(err_msg);
	exit(CMD_NOT_FOUND_STAT);
}

int	execute_command(t_data *data, t_command *cmd)
{
	int		status;
	int		err_type;

	if (cmd->err_message)
	{
		write(2, cmd->err_message, ft_strlen(cmd->err_message));
		write(2, "\n", 1);
		err_type = cmd->err_type;
		clean_data(data);
		exit(get_exit_status(err_type));
	}
	status = handle_descriptors(cmd);
	if (status < 1)
		exit(1);
	status = get_path(data, cmd);
	if (status < 1)
		exit(1);
	if (cmd->path == NULL)
		exit_helper(cmd->name, CMD_NOT_FOUND_ERR);
	if (execve(cmd->path, cmd->args, data->env) == -1)
		exit_helper(cmd->name, strerror(errno));
	return (1);
}

int	execute(t_data *data)
{
	int	status;

	if (!data->commands)
		return (0);
	data->commands = get_first_command(data->commands);
	status = create_pipes(data);
	if (status < 1)
		return (status);
	status = create_processes(data);
	return (status);
}
