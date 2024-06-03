#include "../../includes/builtin.h"

int	builtin_exit(t_data *data)
{
	if (!data)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		minishell_error("exit", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	if (data->commands->args)
	{
		if (data->commands->args[0])
		{
			if (data->commands->args[1])
			{
				if (builtin_exit_validation(data->commands->args[1]) != EXIT_SUCCESS)
					return (NOT_NUMERIC_ERROR);
				if (data->commands->args[2])
				{
					write(STDOUT_FILENO, "exit\n", 5);
					minishell_error("exit", NULL, "too many arguments\n");
					return (EXIT_FAILURE);
				}
				g_exit_status = ft_atoi(data->commands->args[1]) % CHAR_SIZE_COMBINATIONS;
			}
		}
	}
	// Free everything here Yura jan
	exit(g_exit_status);
	return (EXIT_SUCCESS);
}