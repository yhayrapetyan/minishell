#include "minishell.h"

void	*clean_io_fds(t_io_fds *io)
{
	if (!io)
		return (NULL);
	free(io->infile);
	free(io->outfile);
	free(io->delimiter);
	return (NULL);
}

void	*clean_commands(t_command *commands)
{
	t_command *tmp;

	if (!commands)
		return (NULL);
	commands = get_first_command(commands);
	while (commands)
	{
		tmp = commands->next;
		free(commands->name);
		free(commands->path);
		free_arr(commands->args);
		clean_io_fds(commands->io_fds);
		free(commands->io_fds);
		free(commands);
		commands = tmp;
	}
	return (NULL);
}
