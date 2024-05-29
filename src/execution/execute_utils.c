#include "minishell.h"

static int	wait_for_childes(t_data *data)
{
	int i;
	int status;

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

static int allocate_childes_pid(t_data *data)
{
	t_command	*cmd;
	int 		i;

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

int create_processes(t_data *data)
{
	t_command	*cmd;
	int 		status;
	int 		i;

	cmd = get_first_command(data->commands);
	status = allocate_childes_pid(data);
	if (status < 1)
		return (status);
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
		{
			if (cmd->pipe_fd)
			{
				close(cmd->pipe_fd[1]);
				close(cmd->pipe_fd[0]);
			}
		}
		cmd = cmd->next;
	}
	return (wait_for_childes(data));
}
