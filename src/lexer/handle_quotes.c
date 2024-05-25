/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:22:34 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:22:34 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	have_quotes(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '"' || content[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	handle_quotes(t_data *data)
{
	t_token	*temp;

	temp = data->tokens;
	while (temp)
	{
		if (have_quotes(temp->content))
		{
			if (temp->prev && temp->prev->type == HEREDOC)
				temp->delim_in_quotes = 1;
			if (!remove_quotes(&temp))
				return (-1);
			temp->len = ft_strlen(temp->content);
		}
		temp = temp->next;
	}
	return (1);
}
