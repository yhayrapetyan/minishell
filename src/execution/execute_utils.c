/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:06:35 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/30 20:06:35 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipes(t_data *data)
{
	int			*fd;
	t_command	*tmp_cmd;

	tmp_cmd = get_first_command(data->commands);
	while (tmp_cmd)
	{
		if (tmp_cmd->pipe_flag == 1)
		{
			fd = malloc(sizeof(int) * 2);
			if (!fd)
				return (-1);
			if (pipe(fd) == -1)
				return (-8);
			tmp_cmd->pipe_fd = fd;
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (1);
}

static int	wait_for_childes(t_data *data)
{
	int			i;
	int			status;
	t_command	*cmd;

	cmd = get_first_command(data->commands);
	while (cmd)
	{
		if (cmd->pipe_fd)
		{
			close(cmd->pipe_fd[0]);
			close(cmd->pipe_fd[1]);
		}
		cmd = cmd->next;
	}
	i = 0;
	while (i < data->commands_count)
	{
		if (waitpid(data->childes_pid[i], &status, 0) == -1)
			return (-11);
		i++;
	}
	if (status != 0)
		return ((status >> 8) & 0xFF);
	return (0);
}

static int	allocate_childes_pid(t_data *data)
{
	t_command	*cmd;
	int			i;

	i = 0;
	cmd = get_first_command(data->commands);
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	data->commands_count = i;
	data->childes_pid = (pid_t *)malloc(sizeof(pid_t) * i);
	if (!data->childes_pid)
		return (-1);
	return (1);
}

static void	do_parent_staff(t_command *cmd)
{
	if (cmd->is_input_heredoc)
		unlink(cmd->io_fds->infile);
	if (cmd->prev)
	{
		close(cmd->prev->pipe_fd[0]);
		close(cmd->prev->pipe_fd[1]);
	}
}

int	create_processes(t_data *data)
{
	t_command	*cmd;
	int			i;

	cmd = get_first_command(data->commands);
	if (allocate_childes_pid(data) < 1)
		return (-1);
	i = 0;
	while (data->pid != 0 && cmd)
	{
		data->pid = fork();
		data->childes_pid[i++] = data->pid;
		if (data->pid == -1)
			return (-9);
		if (data->pid == 0)
			execute_command(data, cmd);
		else
			do_parent_staff(cmd);
		cmd = cmd->next;
	}
	return (wait_for_childes(data));
}
