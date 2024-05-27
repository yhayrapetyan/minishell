/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:44:22 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/24 13:44:22 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	1 => continue
*	0 => break
*	-1 => malloc err
*   -4 => readline err
*/
static int	validate_line(t_data *data, char **line, t_io_fds *io)
{
	char	*tmp;

	if (!*line)
		return (-4);
	if (ft_strcmp(*line, io->delimiter) == 0)
		return (0);
	if (io->delim_in_quotes == 0 && ft_strchr(*line, '$'))
	{
		tmp = expand_heredoc(data, *line);
		if (!tmp)
			return (-1);
		free(*line);
		*line = tmp;
	}
	return (1);
}

static int	loop(t_data *data, t_io_fds *io, int tmp_fd)
{
	int		status;
	char	*line;

	while (1)
	{
//		line = readline(">");
//		SIGNALS
		line = get_next_line(0);//delete
		line[ft_strlen(line) - 1] = '\0';
		status = validate_line(data, &line, io);
		if (status < 1)
			break ;
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	free(line);
	get_next_line(-1);//delete
	close(tmp_fd);
	return (status);
}

/*
*	1 => success
*	-1 => malloc err
*   -4 => readline err
*	-7 => open err
*/
int	read_heredoc(t_io_fds *io, t_data *data, t_command *cmd)
{
	int		tmp_fd;
	int		status;

	tmp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd == -1)
	{
		cmd->err_message = parse_err(io->infile, strerror(errno));
		if (!cmd->err_message)
			return (-1);
		cmd->err_type = -7;
		return (-7);
	}
	status = loop(data, io, tmp_fd);
	if (status < 0)
		return (status);
	return (1);
}
