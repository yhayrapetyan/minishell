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

int execute_builtin(t_data *data)
{
	if (data->commands->err_message)
	{
		write(2, data->commands->err_message, ft_strlen(data->commands->err_message));
		write(2, "\n", 1);
		if (data->commands->is_input_heredoc)
			unlink(data->commands->io_fds->infile);
		return (get_exit_status(data->commands->err_type, data->commands->err_message));
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
	if (data->commands->is_input_heredoc)
		unlink(data->commands->io_fds->infile);
	if (ft_strcmp(data->commands->name, "exit") == 0)
		g_exit_status = builtin_exit(data);
	return (g_exit_status);
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
