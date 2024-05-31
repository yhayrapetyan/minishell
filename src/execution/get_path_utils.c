/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:09:18 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/30 20:09:18 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_builtins(const char **builtins,
	const char **our_builtins, char *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp((char *)cmd, (char *)builtins[i]) == 0)
		{
			j = 0;
			while (our_builtins[j])
			{
				if (ft_strcmp((char *)cmd, (char *)our_builtins[j]) == 0)
					return (1);
				j++;
			}
			return (-1);
		}
		i++;
	}
	return (0);
}

/*
 *  1 => our_builtin
 *  -1 => other_builtin
 *  0 => not_builtin
 * rm our_from
 */
int	is_builtin(char *cmd)
{
	const char	*builtins[] = {
		".", ":", "[", "alias", "bg", "bind", "break", "builtin",
		"caller", "cd", "command", "compgen", "complete", "compopt",
		"continue", "declare", "dirs", "disown", "echo", "enable",
		"eval", "exec", "exit", "export", "false", "fc", "fg",
		"getopts", "hash", "help", "history", "jobs", "kill", "let",
		"local", "logout", "mapfile", "popd", "printf", "pushd", "pwd",
		"read", "readarray", "readonly", "return", "set", "shift",
		"shopt", "source", "suspend", "test", "times", "trap", "true",
		"type", "typeset", "ulimit", "umask", "unalias", "unset", "wait", NULL
	};
	const char	*our_builtins[] = {
		"echo", "pwd", "cd", "unset", "export", "env", "exit", NULL
	};

	return (check_builtins(builtins, our_builtins, cmd));
}

int	is_relative_path(char *cmd_name)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd_name[i])
	{
		if (cmd_name[i] == '/')
			count++;
		i++;
	}
	if (count == 0)
		return (0);
	return (1);
}
