/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:27:36 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:27:36 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
