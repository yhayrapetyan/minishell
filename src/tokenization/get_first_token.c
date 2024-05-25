/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_first_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:27:51 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:27:51 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_first_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->prev != NULL)
		token = token->prev;
	return (token);
}
