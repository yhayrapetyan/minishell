/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:55:30 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/24 13:55:30 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*clean_io_fds(t_io_fds *io)
{
	if (!io)
		return (NULL);
	free(io->infile);
	free(io->outfile);
	free(io->delimiter);
	return (NULL);
}

void	*clean_commands(t_command *commands)
{
	t_command	*tmp;

	if (!commands)
		return (NULL);
	commands = get_first_command(commands);
	while (commands)
	{
		tmp = commands->next;
		free(commands->name);
		free(commands->path);
		free(commands->err_message);
		free_arr(commands->args);
		clean_io_fds(commands->io_fds);
		free(commands->io_fds);
		free(commands->pipe_fd);
		free(commands);
		commands = tmp;
	}
	return (NULL);
}
