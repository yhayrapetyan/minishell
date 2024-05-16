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

int	set_status(char ch, int status)
{
	if 
}

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
		status = set_status(data->input[i], status);
	}
}
