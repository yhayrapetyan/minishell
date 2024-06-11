/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_empty_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:26:04 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/06/11 19:26:45 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	in_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	remove_token(t_data *data, t_token *token)
{
	t_token	*tmp;

	tmp = get_first_token(data->tokens);
	if (!tmp || !token)
		return (1);
	while (tmp)
	{
		if (tmp == token)
		{
			free(tmp->content);
			tmp->content = NULL;
			free(tmp->orig_content);
			tmp->orig_content = NULL;
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
				data->tokens = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			free(tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	return (1);
}

static int	is_redirection(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == TRUNC)
		return (1);
	if (token->type == APPEND)
		return (1);
	if (token->type == INPUT)
		return (1);
	if (token->type == HEREDOC)
		return (1);
	return (0);
}

int	rm_empty_tokens(t_data *data)
{
	t_token	*tmp;

	tmp = get_first_token(data->tokens);
	while (tmp)
	{
		if (tmp->content[0] == '\0' && \
			!in_quotes(tmp->orig_content) && tmp->type != END && \
			!is_redirection(tmp->prev))
			remove_token(data, tmp);
		tmp = tmp->next;
	}
	return (1);
}
