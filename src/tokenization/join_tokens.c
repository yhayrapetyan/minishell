/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:45:36 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/06/10 12:45:53 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	join_tokens(t_data *data)
{
	t_token	*tmp;
	char	*tmp_content;

	tmp = get_first_token(data->tokens);
	while (tmp)
	{
		if ((tmp->type == WORD || tmp->type == ENV) && tmp->next && \
			(tmp->next->type == WORD || tmp->next->type == ENV))
		{
			tmp_content = tmp->content;
			tmp->content = ft_strjoin(tmp->content, tmp->next->content);
			free(tmp_content);
			if (!tmp->content)
				return (-1);
			remove_token(data, tmp->next);
		}
		else
			tmp = tmp->next;
	}
	return (1);
}
