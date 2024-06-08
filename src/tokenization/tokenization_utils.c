/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:29:00 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:29:00 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_state(char ch, int status)
{
	if (ch == '\'' && status == DEFAULT)
		status = IN_SQUOTE;
	else if (ch == '\"' && status == DEFAULT)
		status = IN_DQUOTE;
	else if (ch == '\'' && status == IN_SQUOTE)
		status = DEFAULT;
	else if (ch == '\"' && status == IN_DQUOTE)
		status = DEFAULT;
	return (status);
}

int	is_separator(char *str, int i)
{
	if (is_white_space(str[i]))
		return (SPACES);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '<')
		return (INPUT);
	else if (str[i] == '>')
		return (TRUNC);
	else if (str[i] == '\0')
		return (END);
	else
		return (0);
}

static int in_quotes(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int remove_token(t_data *data, t_token *token)
{
	t_token *tmp;

	tmp = get_first_token(data->tokens);
	if (!tmp || !token)
		return (1);
	while (tmp)
	{
		if (tmp == token)
		{
			free(tmp->content);
			tmp->content = NULL;
			free(tmp->orig_content);
			tmp->orig_content = NULL;
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
				data->tokens = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			free(tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	return (1);
}

int rm_empty_tokens(t_data *data)
{
	t_token *tmp;

	tmp = get_first_token(data->tokens);
	while (tmp)
	{
		if (tmp->content[0] == '\0' && !in_quotes(tmp->orig_content) && tmp->type != END)
			remove_token(data, tmp);
		tmp = tmp->next;
	}
	return (1);
}


int join_tokens(t_data *data)
{
	t_token	*tmp;
	char 	*tmp_content;

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
