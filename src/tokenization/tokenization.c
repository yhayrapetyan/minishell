/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:28:05 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/16 16:42:21 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * -1 => malloc_err
 * -2 => dquote_err
 * -3 => squote_err
 */
int	tokenization(t_data *data)
{
	int	i;
	int	start;
	int	status;

	i = 0;
	start = 0;
	status = DEFAULT;
	while (data->input[i])
	{
		status = set_state(data->input[i], status);
		if (status == DEFAULT)
			start = save_token(data, start, &i);
		if (start == -1)
			return (-1);
		i++;
	}
	if (status == DEFAULT)
		return (save_token(data, start, &i));
	else
		return (status - 4);
}
