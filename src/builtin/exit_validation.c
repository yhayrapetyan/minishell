/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:59:32 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/14 13:19:15 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

static void	overflow_error(const char *str, t_data *data, \
	unsigned long long nbr, int isneg)
{
	if (!isneg || nbr > (unsigned long long)LLONG_MAX + 1)
	{
		minishell_error("exit", (char *)str, "numeric argument required\n");
		clean_data(data);
		exit(OVERFLOW_STAT);
	}
}

int	ft_atoi_with_check(const char *str, t_data *data)
{
	size_t				i;
	unsigned long long	nbr;
	int					isneg;

	i = 0;
	nbr = 0;
	isneg = 0;
	while (str[i] && is_space(str[i]))
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			isneg = 1;
		++i;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		nbr = (nbr * 10) + (str[i] - '0');
		if (nbr > LLONG_MAX)
			overflow_error(str, data, nbr, isneg);
		++i;
	}
	if (isneg)
		return (-nbr);
	return (nbr);
}

int	builtin_exit_validation(char *arg, t_data *data)
{
	int	i;

	if (!arg)
	{
		minishell_error("exit", "NULL", "not a valid identifier\n");
		g_exit_status = 255;
		return (NOT_NUMERIC_ERROR);
	}
	i = -1;
	while (arg[++i])
	{
		if (i == 0 && (arg[i] == '+' || arg[i] == '-'))
			continue ;
		if (!ft_isdigit(arg[i]))
		{
			minishell_error("exit", arg, "numeric argument required\n");
			g_exit_status = NOT_NUMERIC_STAT;
			return (NOT_NUMERIC_ERROR);
		}
	}
	ft_atoi_with_check(arg, data);
	return (EXIT_SUCCESS);
}
