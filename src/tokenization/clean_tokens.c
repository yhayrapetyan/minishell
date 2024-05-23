/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:27:41 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:27:41 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
