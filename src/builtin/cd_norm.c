/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_norm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skedikia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:46:53 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/04 13:46:54 by skedikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// cd -
static int	cd_previous_move_case(t_data *data)
{
	char	*oldpwd_value;

	if (!data)
	{
		minishell_error("cd", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	oldpwd_value = get_value_from_env(data->env, "OLDPWD");
	if (!oldpwd_value)
	{
		minishell_error("cd", NULL, "OLDPWD not set\n");
		return (EXIT_FAILURE);
	}
	if (chdir(oldpwd_value) == ERROR_VALUE)
	{
		minishell_error("cd", oldpwd_value, "No such file or directory\n");
		return (EXIT_FAILURE);
	}
	write(STDOUT_FILENO, oldpwd_value, ft_strlen(oldpwd_value));
	write(STDOUT_FILENO, "\n", 1);
	return (cd_update_workdirs(data, oldpwd_value));
}

// cd ..
static int	cd_parent_move_case(t_data *data)
{
	char	cwd[PATH_MAX];

	if (!data)
	{
		minishell_error("cd", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	if (chdir("..") == ERROR_VALUE)
	{
		minishell_error("cd", NULL, "chdir error\n");
		return (EXIT_FAILURE);
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		minishell_error("cd", NULL, "getcwd error\n");
		return (EXIT_FAILURE);
	}
	return (cd_update_workdirs(data, cwd));
}

// cd 'path'
static int	cd_path_move_case(t_data *data, char *path)
{
	char	cwd[PATH_MAX];

	if (!data)
	{
		minishell_error("cd", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	if (chdir(path) == ERROR_VALUE)
	{
		minishell_error("cd", path, "No such file or directory\n");
		return (EXIT_FAILURE);
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		minishell_error("cd", NULL, "getcwd error\n");
		return (EXIT_FAILURE);
	}
	return (cd_update_workdirs(data, cwd));
}

// cd
static int	cd_home_move_case(t_data *data)
{
	char	*home_value;

	if (!data)
	{
		minishell_error("cd", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	home_value = get_value_from_env(data->env, "HOME");
	if (!home_value)
	{
		minishell_error("cd", NULL, "HOME not set\n");
		return (EXIT_FAILURE);
	}
	if (chdir(home_value) == ERROR_VALUE)
	{
		minishell_error("cd", home_value, "No such file or directory\n");
		return (EXIT_FAILURE);
	}
	return (cd_update_workdirs(data, home_value));
}

int	change_directory(t_data *data, char *arg)
{
	int		arg_len;
	int		status;

	if (!data)
		return (EXIT_SUCCESS);
	if (arg)
	{
		arg_len = ft_strlen(arg);
		if (arg[0] == '-' && arg_len == 1)
			status = cd_previous_move_case(data);
		else if (arg[0] == '.' && arg[1] == '.' && arg_len == 2)
			status = cd_parent_move_case(data);
		else
			status = cd_path_move_case(data, arg);
	}
	else
		status = cd_home_move_case(data);
	return (status);
}
