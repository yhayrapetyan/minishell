#include "../../includes/builtin.h"

int	builtin_pwd(t_data *data) // actually I don't need data, but maybe we could use pwd in future for something else, so I let it be here.
{
	char	cwd[PATH_MAX];

	if (!data)
	{
		minishell_error("pwd", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		minishell_error("pwd", "NULL", "Directory error\n");
		return (EXIT_FAILURE);
	}
	write(STDOUT_FILENO, cwd, ft_strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}