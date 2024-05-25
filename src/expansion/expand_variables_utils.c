/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:16:44 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:16:44 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_between_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (str[i - 1] == '\"' && str[i + 1] == '\"')
			return (1);
		else
			return (0);
	}
	return (0);
}

int	is_valid_variable(t_data *data, int i)
{
	char	ch;

	ch = data->tokens->content[i + 1];
	if (ch == '$' || ch == ' ' || ch == '=' || ch == '\0')
		return (0);
	if (var_between_quotes(data->tokens->content, i))
		return (0);
	if (!(data->tokens->state == DEFAULT || data->tokens->state == IN_DQUOTE))
		return (0);
	return (1);
}

void	update_state(t_token **token, char ch)
{
	if (ch == '\'' && (*token)->state == DEFAULT)
		(*token)->state = IN_SQUOTE;
	else if (ch == '\'' && (*token)->state == IN_SQUOTE)
		(*token)->state = DEFAULT;
	else if (ch == '"' && (*token)->state == DEFAULT)
		(*token)->state = IN_DQUOTE;
	else if (ch == '"' && (*token)->state == IN_DQUOTE)
		(*token)->state = IN_DQUOTE;
}
