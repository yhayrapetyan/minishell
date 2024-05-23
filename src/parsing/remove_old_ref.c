/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_old_ref.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:36:00 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 17:59:52 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* flag = 1 => infile
* flag = 0 => outfile
*/
int	remove_old_ref(t_io_fds *io, int flag)
{
	if (flag == 1 && io->infile)
	{
		if (io->fd_in == -1 || (io->outfile && io->fd_out == -1))//idk about 2 condition
		{
			printf("false\n");
			printf("in = %d\tout = %d\toutfile = %s\n", io->fd_in, io->fd_out, io->outfile);
			return (0);
		}
		if (io->delimiter != NULL)
		{
			free(io->delimiter);
			io->delimiter = NULL;
			unlink(io->infile);//idk about this
		}
		free(io->infile);
		io->infile = NULL;
		close(io->fd_in);//need to check close err
	}
	else if (flag == 0 && io->outfile)
	{
		if (io->fd_out == -1 || (io->infile && io->fd_in == -1))
			return (0);
		free(io->outfile);
		io->outfile = NULL;
		close(io->fd_out);//need to check close err
	}
	return (1);
}
