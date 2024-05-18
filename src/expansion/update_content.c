#include "minishell.h"

static int handle_empty_var(t_data *data, int i)
{
	char	*var;

	var = ft_substr(data->tokens->content + i + 1, 0, get_var_key_len(data->tokens->content + i + 1));
	if (!var)
		return (-1);
	if (get_env_index(data->env, var) != -1)
	{
		free(var);
		return (-1);//need to handle malloc err
	}
	else
	{
		free(var);
		if (!erase_variable(&data->tokens, data->tokens->content, i))
			return (-1);//need to handle malloc err;
	}
	return (1);
}

int	update_content(t_data *data, char *var_value, int i)
{
	if (!var_value)
		return (handle_empty_var(data, i));
	else
	{
		if (!replace_old_content(&data->tokens, var_value, i))
		{
			free(var_value);
			return (-1);//need to handle malloc err;
		}
	}
	return (1);
}
