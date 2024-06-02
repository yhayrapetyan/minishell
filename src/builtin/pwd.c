#include "../../includes/builtin.h"

int	builtin_pwd(t_data *data)
{
	if (!data)
	{
		minishell_error("pwd", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	if (!data->work_dir)
	{
		minishell_error("pwd", "NULL", "Directory error\n");
		return (EXIT_FAILURE);
	}
	write(STDOUT_FILENO, data->work_dir, ft_strlen(data->work_dir));
	write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}