/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:53:39 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 15:57:38 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	open_infile(t_io_fds *io, char *filename)
{
	if (!remove_old_ref(io, 1))
		return (1);
	io->infile = ft_strdup(filename);
	if (!io->infile)
		return (0);
	// if (io->infile[0] == '\0')
	// 	syntax_err
	io->fd_in = open(io->infile, O_RDONLY);
	// if (io->fd_in == -1)
	// 	open_err
	return (1);
}

int	parse_input(t_command **commands, t_token **tokens)
{
	t_command	*lst_cmd;
	t_token		*tmp;

	lst_cmd = get_last_command(*commands);
	tmp = *tokens;
	if (!init_io_fds(lst_cmd))
		return (0);
	if (!open_infile(lst_cmd->io_fds, tmp->next->content))
		return (0);
	if (tmp->next->next)
		*tokens = tmp->next->next;
	else
		*tokens = tmp->next;
	return (1);
}
