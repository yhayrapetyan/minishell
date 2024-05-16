/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:36:19 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/16 11:36:19 by yuhayrap         ###   ########.fr       */
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

void	init_data(t_data *data, char **env)
{
	data->env = ft_arrdup(env);//need to increment shell level or set to 1
	if (!data->env)
		ft_error(ENV_INIT_ERR, ENV_INIT_STAT);
	if (!init_export(data))
	{
		clean_data(data);
		ft_error(EXPORT_INIT_ERR, EXPORT_INIT_STAT);
	}
	if (!init_work_dir(data))
	{
		clean_data(data);
		ft_error(WDIR_INIT_ERR, WDIR_INIT_STAT);
	}
}
