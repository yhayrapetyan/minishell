/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_echo_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:33:08 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/26 14:43:53 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_empty_var(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp->type == WORD || tmp->type == ENV)
	{
		tmp = tmp->next;
	}
}

int	create_echo_args(t_token **tokens, t_command *last_cmd)
{
	t_token	*tmp
	int		i;
	int		nb_args;

	remove_empty_var(tokens);
	return (1);
}

int	add_echo_args(t_token **tokens, t_command *last_cmd)
{
	return (1);
}