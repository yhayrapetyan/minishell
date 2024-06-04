#include "../../includes/builtin.h"

int	builtin_exit_validation(char *arg)
{
	int	i;

	if (!arg)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		minishell_error("exit", "NULL", "not a valid identifier\n");
		return (NOT_NUMERIC_ERROR);
	}
	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			write(STDOUT_FILENO, "exit\n", 5);
			minishell_error("exit", arg, "numeric argument required\n");
			return (NOT_NUMERIC_ERROR);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}