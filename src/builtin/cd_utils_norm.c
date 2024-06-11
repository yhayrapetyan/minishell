/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_norm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:47:15 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/11 14:25:57 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	cd_update_export_value_oldpwd(t_data *data, int pwd_pos, \
		int oldpwd_pos)
{
	int		status;

	status = EXIT_SUCCESS;
	if (oldpwd_pos != NOT_FOUND)
	{
		status = delete_variable(data, "OLDPWD");
		if (pwd_pos == NOT_FOUND)
		{
			if (data->is_pwd_unset_for_cd == 1)
			{
				status = add_to_enviroment(data, "OLDPWD", NULL);
				return (status);
			}
			status = add_to_enviroment(data, "OLDPWD", data->old_work_dir);
		}
		else
		{
			status = add_to_enviroment(data, "OLDPWD", \
				get_env_value(data->env, "PWD"));
		}
	}
	return (status);
}

int	cd_update_export_values(t_data *data)
{
	int		pwd_pos;
	int		oldpwd_pos;
	int		status;

	if (!data)
		return (EXIT_FAILURE);
	pwd_pos = find_export_variable_position(data->export, "PWD");
	oldpwd_pos = find_export_variable_position(data->export, "OLDPWD");
	status = cd_update_export_value_oldpwd(data, pwd_pos, oldpwd_pos);
	return (status);
}

static int	cd_update_env_value_oldpwd(t_data *data, int pwd_pos, \
		int oldpwd_pos)
{
	int		status;

	status = EXIT_SUCCESS;
	if (oldpwd_pos != NOT_FOUND)
	{
		status = delete_variable(data, "OLDPWD");
		if (pwd_pos == NOT_FOUND)
		{
			if (data->is_pwd_unset_for_cd == 1)
			{
				data->is_pwd_unset_for_cd = 0;
				status = add_to_enviroment(data, "OLDPWD", NULL);
				return (status);
			}
			status = add_to_enviroment(data, "OLDPWD", data->old_work_dir);
		}
		else
			status = add_to_enviroment(data, "OLDPWD", \
				get_env_value(data->env, "PWD"));
	}
	return (status);
}

int	cd_update_env_values(t_data *data)
{
	int		pwd_pos;
	int		oldpwd_pos;
	int		status;

	if (!data)
		return (EXIT_FAILURE);
	pwd_pos = find_env_variable_position(data->env, "PWD");
	oldpwd_pos = find_export_variable_position(data->export, "OLDPWD");
	status = cd_update_env_value_oldpwd(data, pwd_pos, oldpwd_pos);
	if (status != EXIT_SUCCESS)
		return (status);
	status = add_to_enviroment(data, "PWD", data->work_dir);
	return (status);
}
