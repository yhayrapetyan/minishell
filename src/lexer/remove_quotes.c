/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:23:49 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:23:49 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* it takes i and count in arguments because of norm
* function name => len without quotes
*/
static int	lwq(char *content, int i, int count)
{
	int	status;

	status = DEFAULT;
	while (content[i])
	{
		if ((content[i] == '\'' || content[i] == '\"') && status == DEFAULT)
		{
			if (content[i] == '\'')
				status = IN_SQUOTE;
			if (content[i] == '\"')
				status = IN_DQUOTE;
			i++;
			continue ;
		}
		else if ((content[i] == '\'' && status == IN_SQUOTE) || \
				(content[i] == '\"' && status == IN_DQUOTE))
		{
			status = DEFAULT;
			i++;
			continue ;
		}
		count++;
		i++;
	}
	return (count + 1);
}

static void	change_status(t_token **tokens, int *i)
{
	if ((*tokens)->content[*i] == '\'')
		(*tokens)->state = IN_SQUOTE;
	if ((*tokens)->content[*i] == '\"')
		(*tokens)->state = IN_DQUOTE;
	(*i)++;
}

static int	not_opened(t_token **tokens, int i)
{
	char	*str;

	str = (*tokens)->content;
	if ((str[i] == '"' || str[i] == '\'') && (*tokens)->state == DEFAULT)
		return (1);
	return (0);
}

static int	getting_closed(t_token **tokens, int *i)
{
	int		state;
	char	*content;

	content = (*tokens)->content;
	state = (*tokens)->state;
	if ((content[*i] == '\'' && state == IN_SQUOTE) || \
		(content[*i] == '"' && state == IN_DQUOTE))
	{
		(*tokens)->state = DEFAULT;
		(*i)++;
		return (1);
	}
	return (0);
}

int	remove_quotes(t_token **tokens)
{
	char	*new_content;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_content = (char *)malloc(sizeof(char) * lwq((*tokens)->content, 0, 0));
	if (!new_content)
		return (0);
	while ((*tokens)->content[i])
	{
		if (not_opened(tokens, i))
		{
			change_status(tokens, &i);
			continue ;
		}
		else if (getting_closed(tokens, &i))
			continue ;
		new_content[j++] = (*tokens)->content[i++];
	}
	new_content[j] = '\0';
	free((*tokens)->content);
	(*tokens)->content = new_content;
	return (1);
}
