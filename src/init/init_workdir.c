/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_workdir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:57:31 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:57:58 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_work_dir(t_data *data)
{
	char	buff[PATH_MAX];
	char	*wd;

	wd = getcwd(buff, PATH_MAX);
	data->work_dir = ft_strdup(wd);
	if (!data->work_dir)
		return (0);
	if (get_env_index(data->env, "OLDPWD") != -1)
	{
		data->old_work_dir = ft_strdup(get_env_value(data->env, "OLDPWD"));
		if (!data->old_work_dir)
			return (0);
	}
	else
	{
		data->old_work_dir = ft_strdup(wd);
		if (!data->old_work_dir)
			return (0);
	}
	return (1);
}
