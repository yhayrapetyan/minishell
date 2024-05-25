/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:36:27 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/16 11:36:27 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*create_exp_value(char **env, int i)
{
	char	*res;
	int		len;
	int		j;

	len = ft_strlen(env[i]);
	res = (char *)malloc(sizeof(char) * (len + 3));
	if (!res)
		return (NULL);
	j = 0;
	while (env[i][j])
	{
		res[j] = env[i][j];
		if (res[j] == '=')
			break ;
		j++;
	}
	res[++j] = '"';
	while (env[i][j])
	{
		res[j + 1] = env[i][j];
		j++;
	}
	res[++j] = '"';
	res[++j] = '\0';
	return (res);
}

static int	get_opt_len(t_data *data)
{
	int	i;

	i = 1;
	if (get_env_index(data->env, "OLDPWD") == -1)
		i++;
	return (get_env_len(data->env) + i);
}

int	init_export(t_data *data)
{
	int		i;

	data->export = (char **)malloc(sizeof(char *) * (get_opt_len(data)));
	if (!data->export)
		return (0);
	i = 0;
	while (data->env[i])
	{
		data->export[i] = strjoin_and_free("declare -x ",
				create_exp_value(data->env, i));
		if (!data->export[i])
			return (0);
		i++;
	}
	if (get_env_index(data->env, "OLDPWD") == -1)
	{
		data->export[i++] = ft_strdup("declare -x OLDPWD");
		if (!data->export[i - 1])
			return (0);
	}
	data->export[i] = NULL;
	sort_arr(data->export);
	return (1);
}
