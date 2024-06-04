#include "../../includes/builtin.h"

int	builtin_cd_validation(t_data *data)
{
	if (!data)
	{
		minishell_error("cd", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	if (!data->commands->args)
		return (EXIT_SUCCESS); // no arguments
	if (data->commands->args[0])
	{ // I am sure that I won't get null if it gets to this IF statement, but just in case I do these checks so I 100% don't get seg fault
		if (data->commands->args[1])
		{
			if (data->commands->args[2])
			{
				minishell_error("cd", NULL, "too many arguments");
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}