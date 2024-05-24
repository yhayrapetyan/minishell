/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:26:24 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:26:24 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	1 => success
*	-1 => malloc err
*/
int	parse_pipe(t_command **commands, t_token **tokens)
{
	t_command	*last_command;
	t_command	*temp;

	last_command = get_last_command(*commands);
//	last_command->pipe_output = 1;
	temp = add_command(last_command, empty_command());
	if (!temp)
		return (-1);
	*commands = temp;
	*tokens = (*tokens)->next;
	return (1);
}
