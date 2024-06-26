/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:53:39 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/24 20:20:24 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	1 => success
*	-1 => malloc err
*	-6 => ambigous redir
*	-7 => open err
*/
static	int	open_infile(t_io_fds *io, t_token *token, t_command *cmd)
{
	if (!remove_old_ref(io, 1))
		return (1);
	cmd->is_input_heredoc = 0;
	io->infile = ft_strdup(token->content);
	if (!io->infile)
		return (-1);
	if (token->ambiguous == 1 && \
		(io->infile[0] == '\0' || !is_valid_filename(io->infile)))
	{
		cmd->err_message = parse_err(token->orig_content, AMBIGOUS_REDIR_ERR);
		if (!cmd->err_message)
			return (-1);
		cmd->err_type = -6;
		return (-6);
	}
	io->fd_in = open(io->infile, O_RDONLY);
	if (io->fd_in == -1)
	{
		cmd->err_message = parse_err(io->infile, strerror(errno));
		if (!cmd->err_message)
			return (-1);
		cmd->err_type = -7;
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
int	parse_input(t_command **commands, t_token **tokens)
{
	t_command	*lst_cmd;
	t_token		*tmp;
	int			status;

	lst_cmd = get_last_command(*commands);
	tmp = *tokens;
	if (!init_io_fds(lst_cmd))
		return (-1);
	status = open_infile(lst_cmd->io_fds, tmp->next, lst_cmd);
	if (tmp->next->next)
		*tokens = tmp->next->next;
	else
		*tokens = tmp->next;
	return (status);
}
