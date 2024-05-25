/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:16:50 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:16:50 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand(t_data *data)
{
	int		i;
	int		status;
	char	*var_value;

	i = 0;
	while (data->tokens->content[i])
	{
		update_state(&data->tokens, data->tokens->content[i]);
		if (data->tokens->content[i] == '$' && is_valid_variable(data, i))
		{
			var_value = get_variable_value(data, data->tokens->content + i);
			status = update_content(data, var_value, i);
			free(var_value);
			if (status == -1)
				return (0);
		}
		else
			i++;
	}
	return (1);
}

int	expand_variables(t_data *data)
{
	t_token	*temp;

	temp = data->tokens;
	while (data->tokens)
	{
		if (data->tokens->type == ENV)
		{
			if (!expand(data))
				return (-1);
			data->tokens->len = ft_strlen(data->tokens->content);
		}
		data->tokens->state = DEFAULT;
		data->tokens = data->tokens->next;
	}
	data->tokens = temp;
	return (1);
}
