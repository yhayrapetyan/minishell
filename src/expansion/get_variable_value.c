/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:17:22 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:17:22 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_variable_value(t_data *data, char *str)
{
	char	*value;
	char	*var_key;

	var_key = ft_substr(str + 1, 0, get_var_key_len(str));
	if (var_key && get_env_index(data->env, var_key) != -1)
		value = ft_strdup(get_env_value(data->env, var_key));
	else if (var_key && var_key[0] == '?' && var_key[1] == '\0')
		value = ft_itoa(g_exit_status);
	else
		value = NULL;
	free(var_key);
	return (value);
}
