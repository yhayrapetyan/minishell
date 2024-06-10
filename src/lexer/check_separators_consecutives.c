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
		if (token->type >= PIPE && token->prev->type > PIPE)
			return (1);
		if (token->type == END && token->prev->type >= PIPE)
			return (1);
	}
	return (0);
}

static int	separators_consecutive_helper(t_token *tkn, t_command *cmd)
{
	if (tkn->type == END && tkn->prev && tkn->prev->type > PIPE)
		cmd->err_message = syntax_err(SYNTAX_ERR, "newline", 1);
	else if (tkn->type == END && tkn->prev)
		cmd->err_message = syntax_err(SYNTAX_ERR,
				tkn->prev->content, 1);
	else
		cmd->err_message = syntax_err(SYNTAX_ERR, tkn->content, 1);
	return (-5);
}

/*
 * returns
 * 1 => success
 * -5 => syntax err
 */
int	check_separators_consecutive(t_token *tkn, t_command *cmd)
{
	cmd = get_last_command(cmd);
	if (!tkn->prev && tkn->type == PIPE)
	{
		cmd->err_message = syntax_err(SYNTAX_ERR, tkn->content, 1);
		return (-5);
	}
	while (tkn)
	{
		if (tkn->prev && tkn->prev->type == HEREDOC)
			break ;
		if (tkn->type == HEREDOC && tkn->next && \
			(tkn->next->type == END || tkn->next->type == PIPE))
		{
			if (tkn->next->type == END)
				cmd->err_message = syntax_err(SYNTAX_ERR, "newline", 1);
			else
				cmd->err_message = syntax_err(SYNTAX_ERR, "|", 1);
			return (-5);
		}
		if (invalid_consecutive(tkn))
			return (separators_consecutive_helper(tkn, cmd));
		tkn = tkn->next;
	}
	return (1);
}
