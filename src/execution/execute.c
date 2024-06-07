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

static void handle_error(t_data *data, t_command *cmd)
{
	int		err_type;

	write(2, cmd->err_message, ft_strlen(cmd->err_message));
	write(2, "\n", 1);
	err_type = cmd->err_type;
	clean_data(data);
	exit(get_exit_status(err_type));
}

int	execute_command(t_data *data, t_command *cmd)
{
	int		status;

	if (cmd->err_message)
		handle_error(data, cmd);
	status = handle_descriptors(cmd);
	if (status < 1)
		exit(1);
	if (is_builtin(cmd->name))
	{
		data->commands = cmd;
		builtin_run(data);
		clean_data(data);
		exit(g_exit_status);
	}
	status = get_path(data, cmd);
	if (status < 1)
		exit(1);
	if (cmd->path == NULL)
		exit_helper(cmd->name, CMD_NOT_FOUND_ERR);
	if (execve(cmd->path, cmd->args, data->env) == -1)
		exit_helper(cmd->name, strerror(errno));
	return (1);
}

int execute_builtin(t_data *data)
{
	int status;

	status = 0;
	if (data->commands->err_message)
	{
		write(2, data->commands->err_message, ft_strlen(data->commands->err_message));
		write(2, "\n", 1);
		if (data->commands->is_input_heredoc)
			unlink(data->commands->io_fds->infile);
		return (get_exit_status(data->commands->err_type));
	}
	if (data->commands->io_fds)
	{
		data->commands->io_fds->stdin_backup = dup(STDIN_FILENO);
		data->commands->io_fds->stdout_backup = dup(STDOUT_FILENO);
	}
	handle_descriptors(data->commands);
	builtin_run(data);
	if (reset_descriptors(data->commands->io_fds) < 0)
		return (-10);
	if (ft_strcmp(data->commands->name, "exit") == 0)
		builtin_exit(data);
	if (data->commands->is_input_heredoc)
		unlink(data->commands->io_fds->infile);
	return (status);
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
	status = 0;
	if (!data->commands->prev && !data->commands->pipe_fd && is_builtin(data->commands->name))
		status = execute_builtin(data);
	else
		status = create_processes(data);
	return (status);
}
