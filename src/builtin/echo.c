#include "../../includes/builtin.h"

int	builtin_echo(t_data *data)
{
	int	i;

	if (!data)
	{
		minishell_error("echo", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	// I will consider that Yura already dub2() the STDOUT_FILENO with the file descriptor
	if (data->commands->args)
	{
		i = 1; // args[0] is the command name
		while (data->commands->args[i])
		{
			write(STDOUT_FILENO, data->commands->args[i], ft_strlen(data->commands->args[i]));
			if (data->commands->args[i + 1]) // If next argument exists, print space
				write(STDOUT_FILENO, " ", 1);
			++i;
		}
	}
	write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}