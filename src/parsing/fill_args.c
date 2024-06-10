/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:25:21 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:25:21 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	0 => fail
*	1 => success
*/
int	fill_args(t_token **tokens, t_command *last_command)
{
	if (!ft_strcmp(last_command->name, "echo"))
	{
		if (!(last_command->args))
			return (create_echo_args(tokens, last_command));
		else
			return (add_echo_args(tokens, last_command));
	}
	else
	{
		if (last_command && (!last_command->args))
			return (create_args(tokens, last_command));
		else
			return (add_args(tokens, last_command));
	}
}
