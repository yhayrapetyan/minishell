/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:22:12 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:22:12 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse(t_data *data, t_token **token)
{
	int	status;

	status = 0;
	if ((*token)->type == WORD || (*token)->type == ENV)
		status = parse_word(&data->commands, token);
	else if ((*token)->type == PIPE)
		status = parse_pipe(&data->commands, token);
	else if ((*token)->type == INPUT)
		status = parse_input(&data->commands, token);
	else if ((*token)->type == TRUNC)
		status = parse_trunc(&data->commands, token);
	else if ((*token)->type == APPEND)
		status = parse_append(&data->commands, token);
	else if ((*token)->type == HEREDOC)
		status = parse_heredoc(data, &data->commands, token);
	return (status);
}

int	create_commands(t_data *data)
{
	t_token	*temp;
	int		status;
	int		res;
	int		flag;

	temp = data->tokens;
	flag = 0;
	res = 1;
	while (temp && temp->next)
	{
//		 printf("command = %s\n", temp->content);
		if (!temp->prev)
			data->commands = add_command(data->commands, empty_command());
		if (!data->commands)
			return (-1);
		if (flag == 0)
		{
			status = check_separators_consecutive(temp);
			if (status < 1)
				return (status);
			flag = 1;
		}
		if (temp->type == HEREDOC)
			flag = 0;
		status = parse(data, &temp);
		if (temp->type == END)
			break ;
		if (res == 1 && status < 1)//if malloc err return if open error wait
			res = status;
	}
	return (res);
}
