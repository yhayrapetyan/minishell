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

static int	is_input_empty(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		if (!is_white_space(data->input[i]))
			return (0);
		i++;
	}
	return (1);
}
/* returns
 * 1 => success
 * -1 => malloc_err
 * -2 => dquote_err
 * -3 => squote_err
 * -4 => readline_err
 * */
int	lexer(t_data *data)
{
	int status;

	status = 0;
	if (data->input == NULL)
		return (-4);
	if (is_input_empty(data))//if input = '\0' someone throw error?
		return (1);
	add_history(data->input);
	status = tokenization(data);
	if (status < 1)
		return (status);
	print_tokens(data);
	return (1);
}
