/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_trunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:28:41 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 18:06:07 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_trunc(t_io_fds *io, char *filename)
{
	if (!remove_old_ref(io, 0))
		return (1);
	io->outfile = ft_strdup(filename);
	if (!io->outfile)
		return (0);
	// if (io->outfile[0] == '\0')
	// 	syntax_err
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);//need to check permission
	// if (io->fd_out == -1)
	// 	open_err
	return (1);
}


int	parse_trunc(t_command **commands, t_token **tokens)
{
	t_command	*lst_cmd;
	t_token		*tmp;

	lst_cmd = get_last_command(*commands);
	tmp = *tokens;
	if (!init_io_fds(lst_cmd))
		return (0);
	if (!open_trunc(lst_cmd->io_fds, tmp->next->content))
		return (0);
	if (tmp->next->next)
		*tokens = tmp->next->next;
	else
		*tokens = tmp->next;
	return (1);
}

