/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:41:27 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/26 14:04:18 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*generate_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*number;

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, number);
	free(number);
	i++;
	return (name);
}

static int	get_heredoc(t_io_fds *io, t_token *tmp)
{
	io->infile = generate_heredoc_name();
	if (!io->infile)
		return (0);
	io->delimiter = ft_strdup(tmp->next->content);
	io->delim_in_quotes = tmp->next->delim_in_quotes;
	if (!io->delimiter)
		return (0);
	return (1);
}

static int	handle_error(t_data *data, t_io_fds *io, t_token *tmp,
	t_command *lst_cmd)
{
	int	status ;

	if (io->infile)
		free(io->infile);
	if (!get_heredoc(io, tmp))
		return (-1);
	status = read_heredoc(io, data, lst_cmd);
	unlink(io->infile);
	io->fd_in = -1;
	return (status);
}

static int	handle_default(t_data *data, t_io_fds *io, t_token *tmp,
	t_command *lst_cmd)
{
	int	status;

	if (!get_heredoc(io, tmp))
		return (-1);
	status = read_heredoc(io, data, lst_cmd);
	if (status < 0)
	{
		io->fd_in = -1;
		return (status);
	}
	else
	{
		io->fd_in = open(io->infile, O_RDONLY);
		if (io->fd_in == -1)
		{
			lst_cmd->err_message = parse_err(io->infile, strerror(errno));
			if (!lst_cmd->err_message)
				return (-1);
			lst_cmd->err_type = -7;
			return (-7);
		}
	}
	return (1);
}

/*
*	1 => success
*	-1 => malloc err
*   -4 => readline err
*	-7 => open err
*/
int	parse_heredoc(t_data *data, t_command **commands, t_token **tokens)
{
	t_token		*tmp;
	t_command	*lst_cmd;
	t_io_fds	*io;
	int			status;

	tmp = *tokens;
	lst_cmd = get_last_command(*commands);
	if (!init_io_fds(lst_cmd))
		return (-1);
	io = lst_cmd->io_fds;
	if (!remove_old_ref(io, 1))
		status = handle_error(data, io, tmp, lst_cmd);
	else
		status = handle_default(data, io, tmp, lst_cmd);
	if (status < 1)
		return (status);
	if (tmp->next->next)
		*tokens = tmp->next->next;
	else
		*tokens = tmp->next;
	return (1);
}
