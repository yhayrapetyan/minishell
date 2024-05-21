/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:23:15 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:23:15 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_table_header(void)
{
	printf("=============================================================\n");
	printf("                        COMMANDS                             \n");
	printf("=============================================================\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Name          | Path                | Args\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}

static void	print_table_row(t_data *data)
{
	int	i;

	printf("%-13s | %-19s |", data->commands->name, data->commands->path);
	if (data->commands->args)
	{
		i = 0;
		while (data->commands->args[i])
		{
			if (i > 0)
				printf("%*s%-s\n", 38, "", data->commands->args[i]);
			else
				printf(" %s\n", data->commands->args[i]);
			i++;
		}
	}
	else
		printf("(null)\n");
	printf("-------------------------------------------------------------\n");
}

void	print_commands(t_data *data)
{
	t_command	*cmd;

	data->commands = get_first_command(data->commands);
	cmd = data->commands;
	print_table_header();
	while (data->commands)
	{
		print_table_row(data);
		data->commands = data->commands->next;
	}
	printf("\n\n");
	data->commands = cmd;
}
