/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_token_type.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:19:58 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:19:58 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_token_type(t_token **tokens)
{
	int		i;
	t_token	*temp;

	if (!tokens)
		return ;
	*tokens = get_first_token(*tokens);
	temp = *tokens;
	while ((*tokens))
	{
		i = 0;
		while ((*tokens)->content[i])
		{
			if ((*tokens)->content[i] == '$')
			{
				if ((*tokens)->prev && (*tokens)->prev->type == HEREDOC)
					break ;
				(*tokens)->type = ENV;
			}
			i++;
		}
		(*tokens) = (*tokens)->next;
	}
	*tokens = temp;
}
