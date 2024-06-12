/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:59:32 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/11 15:00:24 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit_validation(char *arg, t_data *data)
{
	int	i;

	if (!arg)
	{
		minishell_error("exit", "NULL", "not a valid identifier\n");
		return (NOT_NUMERIC_ERROR);
	}
	i = 0;
	while (arg[i])
	{
		if (i == 0 && (arg[i] == '+' || arg[i] == '-'))
		{
			i++;
			continue ;
		}
		if (!ft_isdigit(arg[i]))
		{
			minishell_error("exit", arg, "numeric argument required\n");
			g_exit_status = NOT_NUMERIC_STAT;
			return (NOT_NUMERIC_ERROR);
		}
		++i;
	}
	ft_atoi_with_check(arg, data);
	return (EXIT_SUCCESS);
}
