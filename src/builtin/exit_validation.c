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

#include "builtin.h"

int	builtin_exit_validation(char *arg)
{
	int	i;

	if (!arg)
	{
		minishell_error("exit", "NULL", "not a valid identifier\n");
		g_exit_status = 255;
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
			g_exit_status = 255;
			return (NOT_NUMERIC_ERROR);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}
