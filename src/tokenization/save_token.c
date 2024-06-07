/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:28:39 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:28:39 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_word(t_data *data, int start, int end)
{
	int		i;
	char	*word;
	t_token	*temp;

	i = 0;
	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (1);
	while (start < end)
	{
		word[i] = data->input[start];
		start++;
		i++;
	}
	word[i] = '\0';
	temp = add_token(data->tokens, &word, WORD, DEFAULT);
	if (!temp)
	{
		free(word);
		return (0);
	}
	data->tokens = temp;
	return (1);
}

static int save_end(t_data *data, int type)
{
	if (type == END && data->tokens->type == SPACES)
	{
		data->tokens->type = END;
		return (1);
	}
	return (0);
}
int	save_separator(t_data *data, int index, int type)
{
	int		i;
	char	*sep;
	int		len;
	t_token	*temp;

	len = 1;
	if (save_end(data, type) == 1)
		return (1);
	if (type == HEREDOC || type == APPEND)
		len++;
	sep = (char *)malloc(sizeof(char) * (len + 1));
	if (!sep)
		return (0);
	i = -1;
	while (++i < len)
		sep[i] = data->input[index + i];
	sep[i] = '\0';
	temp = add_token(data->tokens, &sep, type, DEFAULT);
	if (!temp)
	{
		free(sep);
		return (0);
	}
	data->tokens = temp;
	return (1);
}

static int	save_helper(t_data *data, int *start, int *end, int type)
{
	if (*end != 0 && !is_separator(data->input, *end - 1) && *start != *end)
	{
		if (!save_word(data, *start, *end))
			return (0);
	}
	if (type != SPACES)
	{
		if (!save_separator(data, *end, type))
			return (0);
		if (type == HEREDOC || type == APPEND)
			(*end)++;
	}
	else
	{
		if (data->tokens &&  data->tokens->type == WORD)
		{
			if (!save_separator(data, *end, type))
				return (0);
		}
	}
	(*start) = *end + 1;
	return (1);
}

int	save_token(t_data *data, int start, int *end)
{
	int	type;

	type = is_separator(data->input, *end);
	if (type)
	{
		if (!save_helper(data, &start, end, type))
			return (-1);
	}
	else if (data->input[*end] == '"' || data->input[*end] == '\'')
	{
		if (!save_word(data, start, *end + 1))
			return (-1);
		start = *end + 1;
	}
	return (start);
}
