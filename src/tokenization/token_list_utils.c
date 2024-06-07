/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:05:14 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/31 13:05:14 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_token(t_token *token)
{
	if (!token)
		return ;
	free(token->content);
	free(token->orig_content);
	if (token->prev)
		token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	free(token);
}

t_token	*create_token(char **content, int type, int state)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	token->prev = NULL;
	token->content = *content;
	token->orig_content = ft_strdup(*content);
	if (!token->orig_content)
		return (NULL);
	token->type = type;
	token->state = state;
	token->len = ft_strlen(*content);
	token->ambiguous = 0;
	token->delim_in_quotes = 0;
	return (token);
}

t_token	*add_token(t_token *token, char **content, int type, int state)
{
	t_token	*new_token;

	new_token = create_token(content, type, state);
	if (!new_token)
		return (NULL);
	if (!token)
		return (new_token);
	token->next = new_token;
	new_token->prev = token;
	return (new_token);
}

void	*clean_tokens(t_token *tokens)
{
	t_token	*next;
	t_token	*prev;
	t_token	*tmp;

	if (!tokens)
		return (NULL);
	tmp = tokens->prev;
	while (tokens)
	{
		next = tokens->next;
		free(tokens->content);
		free(tokens->orig_content);
		free(tokens);
		tokens = next;
	}
	while (tmp)
	{
		prev = tmp->prev;
		free(tmp->content);
		free(tmp->orig_content);
		free(tmp);
		tmp = prev;
	}
	return (NULL);
}

t_token	*get_first_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->prev != NULL)
		token = token->prev;
	return (token);
}
