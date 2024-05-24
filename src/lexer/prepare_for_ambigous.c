/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_for_ambigous.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:41:03 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/24 13:41:03 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirection(t_token *token)
{
	if (token->type == INPUT || token->type == TRUNC)
		return (1);
	if (token->type == APPEND || token->type == HEREDOC)
		return (1);
	return (0);
}

static int	in_dqoutes(char *str)
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

int	prepare_for_ambiguous(t_data *data)
{
	t_token	*tmp;

	tmp = get_first_token(data->tokens);
	while (tmp)
	{
		if (tmp->prev && is_redirection(tmp->prev))
		{
			if (tmp->type == ENV && !in_dqoutes(tmp->content))
				tmp->ambiguous = 1;
		}
		tmp = tmp->next;
	}
	return (1);
}
