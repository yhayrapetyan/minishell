#include "minishell.h"

int reset_descriptors(t_io_fds *io)
{
	int	ret;

	ret = 1;
	if (!io)
		return (ret);
	if (io->stdin_backup != -1)
	{
		if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
			ret = -10;
		close(io->stdin_backup);
		io->stdin_backup = -1;
	}
	if (io->stdout_backup != -1)
	{
		if (dup2(io->stdout_backup, STDOUT_FILENO) == -1)
			ret = -10;
		close(io->stdout_backup);
		io->stdout_backup = -1;
	}
	return (ret);
}
