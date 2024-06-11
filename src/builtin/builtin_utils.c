/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:38:26 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/11 14:45:38 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
	i = -1;
	while (data->export[++i])
	{
		j = 0;
		while (data->export[++j])
		{
			if (ft_strncmp(data->export[j - 1] + declare_x_len,
					data->export[j] + declare_x_len,
					ft_strlen(data->export[j] + declare_x_len)) > 0)
			{
				temp = data->export[j - 1];
				data->export[j - 1] = data->export[j];
				data->export[j] = temp;
			}
		}
	}
}

static int	is_space(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

static void	overflow_error(const char *str, t_data *data)
{
	write(1, "exit\n", 5);
	minishell_error("exit", (char *)str, "numeric argument required\n");
	clean_data(data);
	exit(255);
}

int	ft_atoi_with_check(const char *str, t_data *data)
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
		if (nbr > INT_MAX || nbr < INT_MIN)//long long or unsigned long long
			overflow_error(str, data);
		++i;
	}
	if (isneg)
		return (-nbr);
	return (nbr);
}
