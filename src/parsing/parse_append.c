/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:09:41 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 18:53:19 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_append(t_io_fds *io, char *filename)
{
	if (!remove_old_ref(io, 0))
		return (1);
	io->outfile = ft_strdup(filename);
	if (!io->outfile)
		return (0);	
	// if (io->oufile[0] == '\0')
	// 	syntax err
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	// if (io->fd_out == -1)
	// 	open_err
	return (1);
}

int	parse_append(t_command **commands, t_token **tokens)
{
	t_token		*tmp;
	t_command	*lst_cmd;

	tmp = *tokens;
	lst_cmd = get_last_command(*commands);
	if (!init_io_fds(lst_cmd))
		return (0);
	if (!open_append(lst_cmd->io_fds, tmp->next->content))
		return (0);
	if (tmp->next->next)
		*tokens = tmp->next->next;
	else
		*tokens = tmp->next;
	return (1);
}
