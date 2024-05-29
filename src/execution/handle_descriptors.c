#include "minishell.h"

static int dup2_and_close(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		return (-10);
	close(fd1);
	return (1);
}

static int handle_pipe_fds(t_command *cmd)
{
	int status;

	status = 1;
	if (!cmd->prev && cmd->next)
	{
		close(cmd->pipe_fd[0]);
		status = dup2_and_close(cmd->pipe_fd[1], STDOUT_FILENO);
		if (status < 1)
			return (status);
	}
	else
	{
		close(cmd->prev->pipe_fd[1]);
		close(cmd->pipe_fd[0]);
//		close(cmd->prev->pipe_fd[0]);// if rm this line data transfer but yes | yes | head fail
		status = dup2_and_close(cmd->prev->pipe_fd[0], STDIN_FILENO);//cmd->prev
		if (status < 1)
			return (status);
		status = dup2_and_close(cmd->pipe_fd[1], STDOUT_FILENO);
		if (status < 1)
			return (status);
	}
	return (1);
}

int handle_descriptors(t_command *cmd)
{
	int status;

	status = 1;
	if (cmd->io_fds)
	{

		if (cmd->io_fds->infile && cmd->io_fds->fd_in != -1)
		{
			status = dup2_and_close(cmd->io_fds->fd_in, STDIN_FILENO);
			if (cmd->pipe_fd)
				close(cmd->pipe_fd[0]);
		}
		else if (cmd->pipe_fd)
			status = dup2_and_close(cmd->pipe_fd[0], STDIN_FILENO);
		if (status < 1)
			return (status);
		if (cmd->io_fds->outfile && cmd->io_fds->fd_out != -1)
		{
			status = dup2_and_close(cmd->io_fds->fd_out, STDOUT_FILENO);
			if (cmd->pipe_fd)
				close(cmd->pipe_fd[1]);
		}
		else if (cmd->pipe_fd)
			status = dup2_and_close(cmd->pipe_fd[1], STDOUT_FILENO);
		if (status < 1)
			return (status);
	}
	else if (cmd->pipe_fd)
		status = handle_pipe_fds(cmd);
	else if (cmd->prev && cmd->prev->pipe_flag == 1)
	{
		close(cmd->prev->pipe_fd[1]);
		status = dup2_and_close(cmd->prev->pipe_fd[0], STDIN_FILENO);
		if (status < 1)
			return (status);
	}
	return (status);
}
