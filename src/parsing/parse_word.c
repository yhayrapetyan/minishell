/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:26:30 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:26:30 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	contain_space(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

static t_token	*get_new_tokens(char **str)
{
	t_token	*new_tokens;
	t_token	*temp;
	char	*temp_content;
	int		i;

	new_tokens = NULL;
	i = 0;
	while (str[++i])
	{
		temp_content = ft_strdup(str[i]);
		if (!temp_content)
			return (clean_tokens(new_tokens));
		temp = add_token(new_tokens, &temp_content, WORD, DEFAULT);
		if (!temp)
			return (clean_tokens(new_tokens));
		new_tokens = temp;
	}
	temp_content = ft_strdup("");
	temp = add_token(new_tokens, &temp_content, END, DEFAULT);
	if (!temp)
		return (clean_tokens(new_tokens));
	new_tokens = temp;
	return (new_tokens);
}

static int	split_token(t_command *command, char *content)
{
	t_token	*new_tokens;
	char	**str;
	int		status;

	str = ft_split(content, ' ');
	if (!str)
		return (0);
	command->name = ft_strdup(str[0]);
	if (!command->name)
	{
		free_arr(str);
		return (0);
	}
	new_tokens = get_new_tokens(str);
	free_arr(str);
	if (!new_tokens)
		return (0);
	status = fill_args(&new_tokens, command);
	clean_tokens(new_tokens);
	return (status);
}

static int	fill_name(t_command *last_cmd, t_token **temp_token)
{
	if ((*temp_token)->type == ENV && contain_space((*temp_token)->content))
	{
		if (!split_token(last_cmd, (*temp_token)->content))
			return (0);
	}
	else
	{
		last_cmd->name = ft_strdup((*temp_token)->content);
		if (!last_cmd->name)
			return (0);
	}
	return (1);
}

int	parse_word(t_command **commands, t_token **tokens)
{
	t_token		*temp_token;
	t_command	*last_cmd;

	temp_token = (*tokens);
	while (temp_token->type == WORD || temp_token->type == ENV)
	{
		last_cmd = get_last_command(*commands);
		if (temp_token->prev == NULL || \
			(temp_token->prev && temp_token->prev->type == PIPE) || \
			last_cmd->name == NULL)
		{
			if (!fill_name(last_cmd, &temp_token))
				return (0);
			temp_token = temp_token->next;
		}
		else
		{
			if (!fill_args(&temp_token, last_cmd))
				return (0);
		}
	}
	(*tokens) = temp_token;
	return (1);
}
