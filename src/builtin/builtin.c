#include "../../includes/builtin.h"

int	builtin_run(t_data *data)
{
	int	cmd_len;

	if (!data)
		return (NOT_FOUND);
	cmd_len = ft_strlen(data->commands->name);
	if (cmd_len == 6) // export
	{
		if (ft_strncmp(data->commands->name, "export", 6) == 0)
			g_exit_status = builtin_export(data);
	}
	else if (cmd_len == 5) // unset
	{
		if (ft_strncmp(data->commands->name, "unset", 5) == 0)
			g_exit_status = builtin_unset(data);
	}
	else if (cmd_len == 4) // echo
	{
		if (ft_strncmp(data->commands->name, "echo", 4) == 0)
			g_exit_status = builtin_echo(data);
	}
	else if (cmd_len == 3) // pwd, env
	{
		if (ft_strncmp(data->commands->name, "pwd", 3) == 0)
			g_exit_status = builtin_pwd(data);
		else if (ft_strncmp(data->commands->name, "env", 3) == 0)
			g_exit_status = builtin_env(data);
	}
	else if (cmd_len == 2) // cd
	{
		if (ft_strncmp(data->commands->name, "cd", 2) == 0)
			g_exit_status = builtin_cd(data);
	}
	return (NOT_FOUND);
}