/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_separators_consecutives.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:20:34 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:20:34 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	invalid_consecutive(t_token *token)
{
	if (token->prev)
	{
		if (token->type == PIPE && token->prev->type == PIPE)
			return (1);
		if (token->type > PIPE && token->prev->type > PIPE)
			return (1);
		if (token->type == END && token->prev->type >= PIPE)
			return (1);
	}
	return (0);
}

/*
 * returns
 * 1 => success
 * -1 => syntax err
 */
int	check_separators_consecutive(t_token *tkn)
{
	if (!tkn->prev && tkn->type == PIPE)
		return (syntax_err(SYNTAX_ERR, tkn->content, 1));
	while (tkn)
	{
		if (tkn->prev && tkn->prev->type == HEREDOC)
			break ;
		if (invalid_consecutive(tkn))
		{
			if (tkn->type == END && tkn->prev && tkn->prev->type > PIPE)
				return (syntax_err(SYNTAX_ERR, "newline", 1));
			else if (tkn->type == END && tkn->prev)
				return (syntax_err(SYNTAX_ERR, tkn->prev->content, 1));
			else
				return (syntax_err(SYNTAX_ERR, tkn->content, 1));
		}
		tkn = tkn->next;
	}
	return (1);
}

/* ORIG */
// int	check_separators_consecutive(t_token *tkn)
// {
// 	tkn = get_first_token(tkn);
// 	if (tkn->type == PIPE)
// 		return (syntax_err(SYNTAX_ERR, tkn->content, 1));
// 	while (tkn)
// 	{
// 		if (invalid_consecutive(tkn))
// 		{
// 			if (tkn->type == END && tkn->prev && tkn->prev->type > PIPE)
// 				return (syntax_err(SYNTAX_ERR, "newline", 1));
// 			else if (tkn->type == END && tkn->prev)
// 				return (syntax_err(SYNTAX_ERR, tkn->prev->content, 1));
// 			else
// 				return (syntax_err(SYNTAX_ERR, tkn->content, 1));
// 		}
// 		tkn = tkn->next;
// 	}
// 	return (1);
// }
