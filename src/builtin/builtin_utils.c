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
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	else
		perror("");
}

void	data_sort_export(t_data *data)
{
	char	*temp;
	int		declare_x_len;
	int		i;
	int		j;

	if (!data)
		return ;
	declare_x_len = ft_strlen("declare -x ");
	i = 0;
	while (data->export[i])
	{
		j = 1;
		while (data->export[j])
		{
			if (ft_strncmp(data->export[j - 1] + declare_x_len,
						  data->export[j] + declare_x_len,
						  ft_strlen(data->export[j] + declare_x_len)) > 0)
			{
				temp = data->export[j - 1];
				data->export[j - 1] = data->export[j];
				data->export[j] = temp;
			}
			++j;
		}
		++i;
	}
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
			if (export[i][declare_x_len + key_len] == '=' || export[i][declare_x_len + key_len] == '\0')
				return (i);
		}
		++i;
	}
	return (NOT_FOUND);
}

static int	is_space(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

int	ft_atoi(const char *str)
{
	size_t		i;
	long long	nbr;
	int			isneg;

	i = 0;
	nbr = 0;
	isneg = 0;
	while (str[i] && is_space(str[i]))
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			isneg = 1;
		++i;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		nbr = (nbr * 10) + (str[i] - '0');
		++i;
	}
	if (isneg)
		return (-nbr);
	return (nbr);
}