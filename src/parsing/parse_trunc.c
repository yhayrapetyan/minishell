/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_trunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:28:41 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/24 20:21:39 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	1 => success
*	-1 => malloc err
*	-6 => ambigous redir
*	-7 => open err
*/
static int	open_trunc(t_io_fds *io, t_token *token, t_command *cmd)
{
	if (!remove_old_ref(io, 0))
		return (1);
	io->outfile = ft_strdup(token->content);
	if (!io->outfile)
		return (-1);
	if (token->ambiguous == 1 && \
		(io->outfile[0] == '\0' || !is_valid_filename(io->outfile)))
	{
		cmd->err_message = parse_err(token->orig_content, AMBIGOUS_REDIR_ERR);
		if (!cmd->err_message)
			return (-1);
		return (-6);
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->fd_out == -1)
	{
		cmd->err_message = parse_err(io->infile, strerror(errno));
		printf("error = %s\n", cmd->err_message);
		if (!cmd->err_message)
			return (-1);
		return (-7);
	}
	return (1);
}

/*
*	1 => success
*	-1 => malloc err
*	-6 => ambigous redir
*	-7 => open err
*/
int	parse_trunc(t_command **commands, t_token **tokens)
{
	t_command	*lst_cmd;
	t_token		*tmp;
	int			status;

	lst_cmd = get_last_command(*commands);
	tmp = *tokens;
	if (!init_io_fds(lst_cmd))
		return (-1);
	status = open_trunc(lst_cmd->io_fds, tmp->next, lst_cmd);
	if (status < 1)
		return (status);
	if (tmp->next->next)
		*tokens = tmp->next->next;
	else
		*tokens = tmp->next;
	return (1);
}

