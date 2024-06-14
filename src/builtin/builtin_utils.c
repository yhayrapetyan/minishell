/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:38:26 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/14 13:16:38 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
