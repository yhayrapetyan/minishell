/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:50:25 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/24 12:50:25 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* not proud of all of this above */
static t_token	*get_helper_token(t_data *data, char *str, int *index,
	char **tmp_content)
{
	char	*var_value;
	t_token	*tmp_token;
	int		status;
	t_data	tmp_data;

	tmp_token = NULL;
	tmp_token = add_token(tmp_token, tmp_content, ENV, DEFAULT);
	if (!tmp_token)
		return (NULL);
	tmp_data.tokens = tmp_token;
	tmp_data.env = ft_arrdup(data->env);
	if (!tmp_data.env)
		return (clean_tokens(tmp_token));
	var_value = get_variable_value(data, str + *index);
	status = update_content(&tmp_data, var_value, *index);
	if (var_value)
		(*index) += ft_strlen(var_value);
	free(var_value);
	free_arr(tmp_data.env);
	if (status == -1)
		return (clean_tokens(tmp_token));
	return (tmp_token);
}

static char	*new_heredoc_content(t_data *data, char *str, int *index)
{
	char	*res;
	t_token	*tmp_token;
	char	*tmp_content;

	tmp_content = ft_strdup(str);
	if (!tmp_content)
		return (NULL);
	tmp_token = get_helper_token(data, str, index, &tmp_content);
	if (!tmp_token)
	{
		free(tmp_content);
		return (NULL);
	}
	res = ft_strdup(tmp_token->content);
	clean_tokens(tmp_token);
	return (res);
}

char	*expand_heredoc(t_data *data, char *str)
{
	int		i;
	char	*temp;
	int		flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			temp = new_heredoc_content(data, str, &i);
			if (!temp)
				return (NULL);
			if (flag == 1)
				free(str);
			if (!flag)
				flag = 1;
			str = temp;
		}
		else
			i++;
	}
	return (str);
}

