/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_echo_args_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:35:56 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/26 14:36:03 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_echo_args(t_token *temp)
{
	int	i;

	i = 0;
	while (temp && (temp->type == WORD || temp->type == ENV))
	{
		if (temp->type == ENV && temp->join == 1)
		{
			while (temp->type == ENV && temp->join == 1)
				temp = temp->next;
			i++;
		}
		else
		{
			temp = temp->next;
			i++;
		}
	}
	return (i);

}

static int in_dquotes(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (0);
		if (str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	remove_empty_var(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp->type == WORD || tmp->type == ENV)
	{
		if (tmp->type == ENV && tmp->content[0] == '\0' && !in_dquotes(tmp->orig_content))
		{
			tmp = tmp->next;
			if (tmp == (*tokens)->next)
				(*tokens) = (*tokens)->next;
			delete_token(tmp->prev);
		}
		else
			tmp = tmp->next;
	}
	return (1);
}

char	*join_vars(t_token **tokens)
{
	t_token	*temp;
	char	*str;
	char	*temp_content;

	temp = *tokens;
	str = ft_strdup(temp->content);
	if (!str)
		return (NULL);
	while (temp->type == ENV && temp->next->type == ENV
		   && temp->next->join == 1)
	{
		temp_content = ft_strjoin(str, temp->next->content);
		free(str);
		if (!temp_content)
			return (NULL);
		str = temp_content;
		temp = temp->next;
	}
	*tokens = temp;
	return (str);
}
