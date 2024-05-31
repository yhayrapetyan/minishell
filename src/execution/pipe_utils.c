/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:56:45 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/31 12:57:05 by yuhayrap         ###   ########.fr       */
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

int	close_pipes(t_command *cmd, t_command *exception)
{
	cmd = get_first_command(cmd);
	while (cmd)
	{
		if (cmd != exception && cmd->pipe_fd)
		{
			close(cmd->pipe_fd[0]);
			close(cmd->pipe_fd[1]);
		}
		cmd = cmd->next;
	}
	return (1);
}
