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

static int	open_append(t_io_fds *io, t_token *token)
{
	if (!remove_old_ref(io, 0))
		return (1);
	io->outfile = ft_strdup(token->content);
	if (!io->outfile)
		return (-1);
	if (token->ambiguous == 1 && (io->outfile[0] == '\0' || !is_valid_filename(io->outfile)))
	{
		if (!print_ambigous_err(token->orig_content))//need to handle correct exit
			return (-1);
		return (-6);
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	// if (io->fd_out == -1)
	// 	open_err
	return (1);
}

int	parse_append(t_command **commands, t_token **tokens)
{
	t_token		*tmp;
	t_command	*lst_cmd;
	int 		status;

	tmp = *tokens;
	lst_cmd = get_last_command(*commands);
	if (!init_io_fds(lst_cmd))
		return (-1);
	status = open_append(lst_cmd->io_fds, tmp->next);
	if (status < 1)
		return (status);
	if (tmp->next->next)
		*tokens = tmp->next->next;
	else
		*tokens = tmp->next;
	return (1);
}
