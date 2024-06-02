#include "../../includes/builtin.h"

int	split_size(char **split)
{
	int	i;

	if (!split)
		return (-1);
	i = 0;
	while (split[i])
		++i;
	return (i);
}

void	minishell_error(char *cmd, char *arg, char *msg)
{
	if (!cmd)
		return ;
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": ", 2);
	if (arg)
	{
		write(STDERR_FILENO, "`", 1);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, "': ", 3);
	}
	if (!msg)
		perror("");
	else
		write(STDERR_FILENO, msg, ft_strlen(msg));
}

int	find_env_variable_position(char **env, char *key)
{
	int	i;
	int	key_len;

	if (!env || !key)
		return (NOT_FOUND);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0)
		{
			if (env[i][key_len] == '=')
				return (i);
		}
		++i;
	}
	return (NOT_FOUND);
}

int	find_export_variable_position(char **export, char *key)
{
	int	i;
	int	key_len;
	int	declare_x_len;

	if (!export || !key)
		return (NOT_FOUND);
	key_len = ft_strlen(key);
	declare_x_len = ft_strlen("declare -x ");
	i = 0;
	while (export[i])
	{
		if (ft_strncmp(export[i] + declare_x_len, key, key_len) == 0)
		{
			if (export[i][declare_x_len + key_len] == '=' || export[i][declare_x_len + key_len] == '\0') // MUST CHECK AFTER EXPORT COMMAND CREATION
				return (i);
		}
		++i;
	}
	return (NOT_FOUND);
}