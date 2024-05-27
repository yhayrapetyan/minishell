#include "minishell.h"

int	execute_command(t_data *data, t_command *cmd)
{
	char *argv[] = {"/bin/cat", "src/utils/clean_commands.c",NULL};

	if (cmd->err_message)
	{
		printf("%s\n", cmd->err_message);
		if (!cmd->next)
			exit(cmd->err_type * (-1));
	}
	if (cmd->io_fds)
	{
		if (cmd->io_fds->fd_in != -1)
		{
			dup2(cmd->io_fds->fd_in, STDIN_FILENO);
			close(cmd->io_fds->fd_in);
		}
		else if (cmd->pipe_fd)
		{
			dup2(cmd->pipe_fd[0], STDIN_FILENO);
			close(cmd->pipe_fd[0]);
		}
		if (cmd->io_fds->fd_out != -1)
		{
			dup2(cmd->io_fds->fd_out, STDOUT_FILENO);
			close(cmd->io_fds->fd_out);
		}
		else if (cmd->pipe_fd)
		{
			dup2(cmd->pipe_fd[1], STDOUT_FILENO);
			close(cmd->pipe_fd[1]);
		}
	}
	else
	{
		dup2(cmd->pipe_fd[0], STDIN_FILENO);
		close(cmd->pipe_fd[0]);
		dup2(cmd->pipe_fd[1], STDOUT_FILENO);
		close(cmd->pipe_fd[1]);
	}
	if (cmd->pipe_fd)
	{
		if (cmd->pipe_fd[0] != -1)
			close(cmd->pipe_fd[0]);
		if (cmd->pipe_fd[1] != -1)
			close(cmd->pipe_fd[1]);
	}
	execve("/bin/cat", argv, data->env);
	return (1);
}

//int wait_for_childes(t_data *data)
//{
//
//}

int close_parents(t_command *cmd)
{
	close(cmd->pipe_fd[1]);
	close(cmd->pipe_fd[0]);
	return (1);
}

int create_processes(t_data *data)
{
	t_command	*cmd;

	cmd = data->commands;
	while (data->pid != 0 && cmd)
	{
		data->pid = fork();
		if (data->pid == -1)
			return (-9);
		if (data->pid == 0)
			execute_command(data, cmd);
//		else
//			close_parents(cmd);
		cmd = cmd->next;
	}
//	wait_for_childes(data)
	return (1);
}

int execute(t_data *data)
{
	int	status;

	if (!data->commands)
		return (0);
	status = create_pipes(data);
	if (status < 1)
		exit(status * -1);//fix
	status = create_processes(data);
	if (status < 1)
		exit(status * -1);//fix
	return (1);
}
