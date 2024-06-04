#include "../../includes/builtin.h"

int	builtin_env(t_data *data)
{
	int	i;

	if (!data)
	{
		minishell_error("env", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	if (!data->env)
	{
		minishell_error("env", NULL, "No such file or directory\n");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (data->env[i])
	{
		if (ft_strchr(data->env[i], '=') != NULL) // We add this check, so keys with no '=' character will not display on the screen, but I think it's not necessary
		{
			write(STDOUT_FILENO, data->env[i], ft_strlen(data->env[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		++i;
	}
	return (EXIT_SUCCESS);
} 