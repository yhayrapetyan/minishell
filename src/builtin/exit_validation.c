/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:59:32 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/10 12:53:05 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_exit_validation(char *arg)
{
	int	i;

	if (!arg)
	{
		write(STDOUT_FILENO, "exit\n", 5);
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
			write(STDOUT_FILENO, "exit\n", 5);
			minishell_error("exit", arg, "numeric argument required\n");
			return (NOT_NUMERIC_ERROR);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}
