/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skedikia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:28:14 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/04 14:28:24 by skedikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_export_validation(char *arg)
{
	int	i;

	if (!arg)
	{
		minishell_error("export", "NULL", "not a valid identifier\n");
		return (EXIT_FAILURE);
	}
	if ((arg[0] != '_') && (ft_isdigit(arg[0]) || !ft_isalpha(arg[0])))
	{
		minishell_error("export", arg, "not a valid identifier\n");
		return (EXIT_FAILURE);
	}
	i = 1;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]))
		{
			if (arg[i] == '=')
				return (EXIT_SUCCESS);
			minishell_error("export", arg, "not a valid identifier\n");
			return (EXIT_FAILURE);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}
