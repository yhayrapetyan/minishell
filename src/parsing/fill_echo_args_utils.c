/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_echo_args_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:35:56 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/31 13:10:38 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_echo_args(t_token *temp)
{
	int	i;

	i = 0;
	while (temp && (temp->type == WORD || temp->type == ENV || temp->type == SPACES))
	{
		if ((temp->type == ENV || temp->type == WORD))
			i++;
		temp = temp->next;
	}
	return (i);
}

static int	in_dquotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (0);
		if (str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	remove_empty_var(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp->type == WORD || tmp->type == ENV)
	{
		if (tmp->type == ENV && tmp->content[0] == '\0' && \
			!in_dquotes(tmp->orig_content))
		{
			tmp = tmp->next;
			if (tmp == (*tokens)->next)
				(*tokens) = (*tokens)->next;
			delete_token(tmp->prev);
		}
		else
			tmp = tmp->next;
	}
	return (1);
}
