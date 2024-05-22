#include "minishell.h"

static int validate_line(t_data *data, char **line, t_io_fds *io)
{
	char	*tmp;

	if (!*line)
	{
//		error_msg
		return (0);
	}
	if (ft_strcmp(*line, io->delimiter) == 0)
		return (0);
	if (io->delim_in_quotes && ft_strchr(*line, '$'))
	{
		tmp = expand_heredoc(data, line);
		if (!tmp)
			return (-1);//need to check line leaks
		*line = tmp;
	}
	return (1);
}

int read_heredoc(t_io_fds *io, t_data *data)
{
	int 	tmp_fd;
	char	*line;
	int 	status;

	tmp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
//	if (tmp_fd == -1)
//		open_err
	while (1)
	{
//		line = readline(">");
//		SIGNALS
		line = get_next_line(0);//delete
		status = validate_line(data, &line, io);
		if (status < 1)
			break ;
		write(tmp_fd, line, ft_strlen(line));//change to put_fd
		free(line);
	}
	free(line);
	get_next_line(-1);//delete
	close(tmp_fd);//CLOSE ERR
	if (status < 1)//maybe before close idk
		return (status);
	return (1);
}

