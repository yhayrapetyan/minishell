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

static int	validate_line(t_data *data, char **line, t_io_fds *io)
{
	char	*tmp;

	if (!*line)
	{
//		error_msg here-document delimited by end-of-file: wanted
		return (-7);
	}
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

int	read_heredoc(t_io_fds *io, t_data *data)
{
	int		tmp_fd;
	char	*line;
	int		status;

	tmp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd == -1)
	{
		if (!parse_err(io->infile, strerror(errno)))
			return (-1);
		return (-7);
	}
	while (1)
	{
//		line = readline(">");
//		SIGNALS
		line = get_next_line(0);//delete
		line[ft_strlen(line) - 1] = '\0';
		status = validate_line(data, &line, io);
		if (status < 1)
			break ;
		write(tmp_fd, line, ft_strlen(line));//change to put_fd
		write(tmp_fd, "\n", 1);
		free(line);
	}
	free(line);
	get_next_line(-1);//delete
	close(tmp_fd);//CLOSE ERR
	if (status < 0)//maybe before close idk
		return (status);
	return (1);
}

