#include "../../includes/builtin.h"

static void	move_split_elements_except_one(char **split_1, char **split_2, int pos)
{
	int	i;
	int	j;

	if (!split_1 || !split_2)
		return ;
	i = 0;
	j = 0;
	while (split_2[j])
	{
		if (j == pos)
		{
			++j;
			if (split_2[j] == NULL)
				break ;
		}
		split_1[i] = split_2[j];
		++j;
		++i;
	}
	split_1[i] = NULL;
}

static int	delete_from_export(t_data *data, char *arg)
{
	int		pos;
	char	**new_export;

	if (!data)
		return (EXIT_FAILURE);
	if (!arg)
		return (EXIT_SUCCESS);
	pos = find_export_variable_position(data->export, arg);
	if (pos == NOT_FOUND)
		return (EXIT_SUCCESS);
	new_export = (char **)malloc(sizeof(char *) * (split_size(data->export))); // We dont do 'size - 1' for NULL terminator.
	if (!new_export)
		return (EXIT_FAILURE);
	move_split_elements_except_one(new_export, data->export, pos);
	free(data->export[pos]);
	free(data->export);
	data->export = new_export;
	return (EXIT_SUCCESS);
}

static int	delete_from_env(t_data *data, char *arg)
{
	int		pos;
	char	**new_env;

	if (!data)
		return (EXIT_FAILURE);
	if (!arg)
		return (EXIT_SUCCESS);
	pos = find_env_variable_position(data->env, arg);
	if (pos == NOT_FOUND)
		return (EXIT_SUCCESS);
	new_env = (char **)malloc(sizeof(char *) * (split_size(data->env))); // We dont do 'size - 1' for NULL terminator.
	if (!new_env)
		return (EXIT_FAILURE);
	move_split_elements_except_one(new_env, data->env, pos);
	free(data->env[pos]);
	free(data->env);
	data->env = new_env;
	return (EXIT_SUCCESS);
}

static int	delete_variable(t_data *data, char *arg)
{
	if (!data)
		return (EXIT_FAILURE);
	if (!arg)
		return (EXIT_SUCCESS);
	if (delete_from_env(data, arg) == EXIT_FAILURE)
	{
		minishell_error("unset", "NULL", "env delete error\n");
		return (EXIT_FAILURE);
	}
	if (delete_from_export(data, arg) == EXIT_FAILURE)
	{
		minishell_error("unset", "NULL", "export delete error\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	builtin_unset(t_data *data)
{
	int	i;
	int	status;

	if (!data)
	{
		minishell_error("unset", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	if (!data->commands->args)
		return (EXIT_SUCCESS); // no arguments, nothing to unset
	i = 1; // args[0] is command name
	while (data->commands->args[i])
	{
		// We can do validation check for argument, but I decided not :), it won't effect on result, but could optimize it
		status = delete_variable(data, data->commands->args[i]);
		++i;
	}
	return (status);
}