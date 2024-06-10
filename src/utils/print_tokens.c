/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:27:59 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:27:59 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_table_header(void)
{
	printf("=============================================================\n");
	printf("                 TOKENS                                      \n");
	printf("=============================================================\n");
	printf("-------------------------------------------------------------\n");
	printf("orig_content       | content            | type          | state");
	printf("         | len  | ambiguous | delim_in quotes\n");
	printf("-------------------------------------------------------------\n");
}

char	*get_type(t_data *data)
{
	int	type;

	type = data->tokens->type;
	if (type == 1)
		return ("SPACES");
	else if (type == 2)
		return ("WORD");
	else if (type == 3)
		return ("ENV");
	else if (type == 4)
		return ("PIPE");
	else if (type == 5)
		return ("INPUT");
	else if (type == 6)
		return ("TRUNC");
	else if (type == 7)
		return ("HEREDOC");
	else if (type == 8)
		return ("APPEND");
	else if (type == 9)
		return ("END");
	return ("UNDEFINED");
}

char	*get_state(t_data *data)
{
	int	state;

	state = data->tokens->state;
	if (state == 0)
		return ("DEFAULT");
	else if (state == 1)
		return ("IN_SQUOTES");
	else if (state == 2)
		return ("IN_DQUOTES");
	return ("UNDEFINED");
}

void	print_table_row(t_data *data)
{
	t_token		*temp;
	char		*type;
	char		*state;

	temp = data->tokens;
	type = get_type(data);
	state = get_state(data);
	printf("%-18s | %-18s | %-13s | %-13s | %-3d | %-10d | %d\n",
		temp->orig_content, temp->content,
		type, state, temp->len, temp->ambiguous, temp->delim_in_quotes);
}

void	print_tokens(t_data *data)
{
	t_token	*temp;

	data->tokens = get_first_token(data->tokens);
	temp = data->tokens;
	print_table_header();
	while (data->tokens)
	{
		print_table_row(data);
		data->tokens = data->tokens->next;
	}
	printf("\n\n");
	data->tokens = temp;
}
