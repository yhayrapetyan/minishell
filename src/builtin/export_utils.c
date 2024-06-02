#include "../../includes/builtin.h"

char	*create_env_variable(char *key, char *value)
{
	char	*env_var;
	char	*temp;

	if (!key || !value)
		return (NULL);
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	env_var = ft_strjoin(temp, value);
	free(temp);
	return (env_var);
}

char	*create_export_variable(char *key, char *value)
{
	char	*export_var;
	char	*temp;

	if (!key)
		return (NULL);
	temp = ft_strjoin("declare -x ", key);
	if (!value)
		return (temp);
	export_var = ft_strjoin(temp, "=\"");
	free(temp);
	if (!export_var)
		return (NULL);
	temp = ft_strjoin(export_var, value);
	free(export_var);
	if (!temp)
		return (NULL);
	export_var = ft_strjoin(temp, "\"");
	free(temp);
	return (export_var);
}

int	add_new_env_variable(t_data *data, char *line)
{
	char	**new_env;
	int		size;
	int		i;

	if (!data || !line)
		return (EXIT_FAILURE);
	size = split_size(data->env) + 1; // +1 for new one
	new_env = (char **)malloc(sizeof(char *) * (size + 1)); // +1 for NULL
	if (!new_env)
		return (EXIT_FAILURE);
	i = 0;
	while (data->env[i])
	{
		new_env[i] = data->env[i];
		++i;
	}
	new_env[i] = line;
	new_env[i + 1] = NULL;
	free(data->env);
	data->env = new_env;
	return (EXIT_SUCCESS);
}

int	add_new_export_variable(t_data *data, char *line)
{
	char	**new_export;
	int		size;
	int		i;

	if (!data || !line)
		return (EXIT_FAILURE);
	size = split_size(data->export) + 1; // +1 for new one
	new_export = (char **)malloc(sizeof(char *) * (size + 1)); // +1 for NULL
	if (!new_export)
		return (EXIT_FAILURE);
	i = 0;
	while (data->export[i])
	{
		new_export[i] = data->export[i];
		++i;
	}
	new_export[i] = line;
	new_export[i + 1] = NULL;
	free(data->export);
	data->export = new_export;
	// SORT EXPORT HERE !
	return (EXIT_SUCCESS);
}

int	update_env_variables(t_data *data, char *key, char *value, char *line)
{
	int	pos;

	if (!data || !key)
		return (EXIT_FAILURE);
	if (!value || !line) // For ENV, if value or line is NULL, we don't add/update
		return (EXIT_SUCCESS);
	pos = find_env_variable_position(data->env, key);
	if (pos == NOT_FOUND) // If not found, create new env **
		return (add_new_env_variable(data, line));
	free(data->env[pos]);
	data->env[pos] = line; // else just update current key
	return (EXIT_SUCCESS);
}

int	update_export_variables(t_data *data, char *key, char *value, char *line)
{
	int	pos;

	if (!data || !key || !line) // for export, line can't come ass NULL
		return (EXIT_FAILURE);
	pos = find_export_variable_position(data->export, key);
	if (pos == NOT_FOUND) // If not found, create new export **
		return (add_new_export_variable(data, line));
	if (!value) // For EXPORT, if value is NULL, we don't update
		return (EXIT_SUCCESS);
	free(data->export[pos]);
	data->export[pos] = line; // else just update current key
	return (EXIT_SUCCESS);
}