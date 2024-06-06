/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_descriptors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:34:24 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/31 12:34:24 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dup2_and_close(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		return (-10);
	close(fd1);
	return (1);
}

static int	handle_pipe_fds(t_command *cmd)
{
	int	status;

	status = 1;
	if (!cmd->prev && cmd->next)
	{
		close(cmd->pipe_fd[0]);
		status = dup2_and_close(cmd->pipe_fd[1], STDOUT_FILENO);
		if (status < 1)
			return (status);
		close_pipes(cmd, cmd);
	}
	else
	{
		close(cmd->prev->pipe_fd[1]);
		close(cmd->pipe_fd[0]);
		status = dup2_and_close(cmd->prev->pipe_fd[0], STDIN_FILENO);
		if (status < 1)
			return (status);
		status = dup2_and_close(cmd->pipe_fd[1], STDOUT_FILENO);
		if (status < 1)
			return (status);
		close_pipes(cmd, cmd);
	}
	return (1);
}

static int handle_one_cmd_io_fds(t_command *cmd)
{
	int status;

	status = 1;
	if (cmd->io_fds->infile && cmd->io_fds->fd_in != -1)
		status = dup2_and_close(cmd->io_fds->fd_in, STDIN_FILENO);
	if (status < 1)
		return (status);
	if (cmd->io_fds->outfile && cmd->io_fds->fd_out != -1)
		status = dup2_and_close(cmd->io_fds->fd_out, STDOUT_FILENO);
	return (status);
}

static int	handle_io_fds(t_command *cmd)
{
	int	status;

	status = 1;
	if (cmd->io_fds->infile && cmd->io_fds->fd_in != -1)
		status = dup2_and_close(cmd->io_fds->fd_in, STDIN_FILENO);
	else if (cmd->prev && cmd->prev->pipe_fd)
		status = dup2_and_close(cmd->prev->pipe_fd[0], STDIN_FILENO);
	close(cmd->pipe_fd[0]);
	if (status < 1)
		return (status);
	if (cmd->io_fds->outfile && cmd->io_fds->fd_out != -1)
		status = dup2_and_close(cmd->io_fds->fd_out, STDOUT_FILENO);
	else if (cmd->pipe_fd)
		status = dup2_and_close(cmd->pipe_fd[1], STDOUT_FILENO);
	close(cmd->pipe_fd[1]);
	close_pipes(cmd, cmd);
	return (status);
}

int	handle_descriptors(t_command *cmd)
{
	int	status;

	status = 1;
	if (cmd->pipe_fd && cmd->io_fds)
		status = handle_io_fds(cmd);
	else if (cmd->pipe_fd)
		status = handle_pipe_fds(cmd);
	else if (!cmd->pipe_fd && cmd->io_fds)
		status = handle_one_cmd_io_fds(cmd);
	else if (cmd->prev && cmd->prev->pipe_flag == 1)
	{
		close(cmd->prev->pipe_fd[1]);
		if (cmd->io_fds && cmd->io_fds->infile && cmd->io_fds->fd_in != -1)
			status = dup2_and_close(cmd->io_fds->fd_in, STDIN_FILENO);
		else
			status = dup2_and_close(cmd->prev->pipe_fd[0], STDIN_FILENO);
		if (status < 1)
			return (status);
		if (cmd->io_fds && cmd->io_fds->outfile && cmd->io_fds->fd_out != -1)
			status = dup2_and_close(cmd->io_fds->fd_out, STDOUT_FILENO);
		if (status < 1)
			return (status);
		close_pipes(cmd, cmd);
	}
	return (status);
}
