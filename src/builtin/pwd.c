/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skedikia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:29:02 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/04 14:29:03 by skedikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(t_data *data)
{
	char	cwd[PATH_MAX];

	if (!data)
	{
		minishell_error("pwd", "NULL", "Data error\n");
		return (EXIT_FAILURE);
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		minishell_error("pwd", "NULL", "Directory error\n");
		return (EXIT_FAILURE);
	}
	write(STDOUT_FILENO, cwd, ft_strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
