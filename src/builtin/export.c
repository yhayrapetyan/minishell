#include "../../includes/builtin.h"

static char	*separate_key(char *line)
{
	char	*new_key;
	int		i;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '=')
		++i;
	new_key = (char *)malloc(sizeof(char) * (i + 1));
	if (!new_key)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '=')
	{
		new_key[i] = line[i];
		++i;
	}
	new_key[i] = '\0';
	return (new_key);
}

static char	*separate_value_norm(char *line, int start)
{
	char	*new_value;
	int		i;

	if (!line)
		return (NULL);
	i = 0;
	while (line[start + i])
		++i;
	if (i == 0)
		return (NULL);
	new_value = (char *)malloc(sizeof(char) * (i + 1));
	if (!new_value)
		return (NULL);
	i = 0;
	while (line[start + i])
	{
		new_value[i] = line[start + i];
		++i;
	}
	new_value[i] = '\0';
	return (new_value);
}

static char	*separate_value(char *line)
{
	char	*new_value;
	int		start;

	if (!line)
		return (NULL);
	start = 0;
	while (line[start] && line[start] != '=')
		++start;
	if (line[start] == '=')
	{
		if (line[start + 1] == '\0') // The empty "" value case
		{
			new_value = (char *)malloc(sizeof(char) * (1));
			if (!new_value)
				return (NULL);
			new_value[0] = '\0';
			return (new_value);
		}
		else
			++start;
	}
	else if (line[start] == '\0')
		return (NULL);
	new_value = separate_value_norm(line, start);
	return (new_value);
}

static int	add_to_enviroment(t_data *data, char *key, char *value)
{
	char	*new_env_var;
	char	*new_export_var;
	int		status;

	if (!data)
		return (EXIT_FAILURE);
	new_env_var = create_env_variable(key, value); // We don't check for NULL, cause if it's NULL, we just avoid adding in ENV variables.
	new_export_var = create_export_variable(key, value);
	if (!new_export_var) // If here is NULL, something went really wrong.
	{
		free(new_env_var);
		return (EXIT_FAILURE);
	}
	status = update_env_variables(data, key, value, new_env_var);
	status = update_export_variables(data, key, value, new_export_var);
	return (status);
}

static int	export_variable(t_data *data, char *arg)
{
	char	*key;
	char	*value;
	int		status;

	if (!data || !arg)
		return (EXIT_FAILURE);
	key = separate_key(arg);
	if (!key)
	{
		minishell_error("export", arg, "Variable Exporting error\n");
		return (EXIT_FAILURE);
	}
	value = separate_value(arg); // if value is NULL, it means we will add in EXPORT variables, but not in ENV variables.
								 // So we don't need to check for NULL here. EVEN IF MALLOC was actually NULL, I am still gonna look it as OK variable.
	status = add_to_enviroment(data, key, value);
	free(key);
	free(value);
	if (status == EXIT_FAILURE)
		minishell_error("export", arg, "Variable Exporting error\n"); // Maybe malloc error, maybe adding to enviroment error.
	return (status);
}

static int	builtin_export_no_args(char **export)
{
	int	i;

	if (!export)
		return (EXIT_SUCCESS); // If EXPORT variables doesn't exists, it's ok no ?
	i = 0;
	while (export[i])
	{
		printf("%s\n", export[i]);
		++i;
	}
	return (EXIT_SUCCESS);
}

int	builtin_export(t_data *data)
{
	int	i;
	int	status;

	if (!data)
	{
		minishell_error("export", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	status = EXIT_SUCCESS;
	i = 1; // 1, because args[0] is the command name, which we already checked.
	if (data->commands->args)
	{
		while (data->commands->args[i])
		{
			if (builtin_export_validation(data->commands->args[i]) == EXIT_FAILURE)
				status = EXIT_FAILURE;
			else
				status = export_variable(data, data->commands->args[i]);
			++i;
		}
	}
	else
		status = builtin_export_no_args(data->export);
	return (status);
}