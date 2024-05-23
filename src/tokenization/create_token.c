/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:27:48 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:27:48 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (token);
}
