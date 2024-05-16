/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:04:18 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/16 16:27:45 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char ch)
{
	if ((ch > 8 && ch < 15) || ch == 32)//need to check range
		return (1);
	return (0);
}

static int	is_input_spaces(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		if (!is_space(data->input[i]))
			return (0);
		i++;
	}
	return (1);
}

int	lexer(t_data *data)
{
	if (data->input == NULL)
	{
		clean_data(data);
		ft_error(RLINE_ERR, RLINE_STAT);
	}
	if (is_input_spaces(data))//if input = '\0' someone throw error?
		return (1);
	add_history(data->input);
	if (!tokenization(data))
		return (0);
	return (1);
}
