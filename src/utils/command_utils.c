/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:21:40 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:21:40 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*empty_command(void)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->name = NULL;
	command->path = NULL;
	command->args = NULL;
	command->err_message = NULL;
	command->err_type = 0;
//	command->pipe_output = 0;
//	command->pipe_fd = 0;
	command->io_fds = NULL;
	command->next = NULL;
	command->prev = NULL;
	return (command);
}

t_command	*add_command(t_command *old_command, t_command *new_command)
{
	if (!new_command)
		return (NULL);
	if (!old_command)
		return (new_command);
	old_command->next = new_command;
	new_command->prev = old_command;
	return (new_command);
}

t_command	*get_last_command(t_command *command)
{
	if (!command)
		return (NULL);
	while (command->next)
		command = command->next;
	return (command);
}

t_command	*get_first_command(t_command *command)
{
	if (!command)
		return (NULL);
	while (command->prev)
		command = command->prev;
	return (command);
}
