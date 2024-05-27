#include "minishell.h"

int create_pipes(t_data *data)
{
	int 		*fd;
	t_command	*tmp_cmd;

	tmp_cmd = data->commands;
	while (tmp_cmd)
	{
		if (tmp_cmd->pipe_flag || (tmp_cmd->prev && tmp_cmd->prev->pipe_flag))
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