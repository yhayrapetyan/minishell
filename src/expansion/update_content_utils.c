/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_content_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:17:31 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:17:31 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	erase_variable(t_token **token, char *content, int index)
{
	int		i;
	int		j;
	int		len;
	char	*new_content;

	i = 0;
	j = 0;
	len = ft_strlen(content) - get_var_key_len(content + index);
	new_content = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_content)
		return (0);
	while (content[i])
	{
		if (content[i] == '$' && i == index)
		{
			i = i + get_var_key_len(content + index) + 1;
			if (content[i] == '\0')
				break ;
		}
		new_content[j++] = content[i++];
	}
	new_content[j] = '\0';
	free((*token)->content);
	(*token)->content = new_content;
	return (1);
}

static void	copy_var_value(char *new_content, char *var_value, int *j)
{
	int	i;

	i = 0;
	while (var_value[i])
	{
		new_content[*j] = var_value[i];
		i++;
		(*j)++;
	}
}

int	replace_old_content(t_token **tokens, char *var_value, int index)
{
	char	*new_content;
	int		len;
	int		i;
	int		j;

	len = ft_strlen((*tokens)->content) - get_var_key_len((*tokens)->content + index) + ft_strlen(var_value);//need to check range
	new_content = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_content)
		return (0);
	i = 0;
	j = 0;
	while ((*tokens)->content[i])
	{
		if ((*tokens)->content[i] == '$' && i == index)
		{
			copy_var_value(new_content, var_value, &j);
			i = i + get_var_key_len((*tokens)->content + index) + 1;
			if ((*tokens)->content[i] == '\0')
				break ;
		}
		new_content[j++] = (*tokens)->content[i++];
	}
	new_content[j] = '\0';
	free((*tokens)->content);
	(*tokens)->content = new_content;
	return (1);
}
