/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:06:23 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 15:11:33 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_io_fds(t_command	*command)
{
	if (!command)
		return (0);
	if (!command->io_fds)
	{
		command->io_fds = (t_io_fds *)malloc(sizeof(t_io_fds));
		if (!command->io_fds)
			return (0);
		command->io_fds->infile = NULL;
		command->io_fds->outfile = NULL;
		command->io_fds->delimiter = NULL;
		command->io_fds->delim_in_quotes = 0;
		command->io_fds->fd_in = -1;
		command->io_fds->fd_out = -1;
	}
	return (1);
}
