/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skedikia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:27:48 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/04 14:27:57 by skedikia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*separate_key(char *line)
{
	char	*new_key;
	int		i;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '=')
		++i;
	new_key = (char *)malloc(sizeof(char) * (i + 1));
	if (!new_key)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '=')
	{
		new_key[i] = line[i];
		++i;
	}
	new_key[i] = '\0';
	return (new_key);
}

static char	*separate_value_norm(char *line, int start)
{
	char	*new_value;
	int		i;

	if (!line)
		return (NULL);
	i = 0;
	while (line[start + i])
		++i;
	if (i == 0)
		return (NULL);
	new_value = (char *)malloc(sizeof(char) * (i + 1));
	if (!new_value)
		return (NULL);
	i = 0;
	while (line[start + i])
	{
		new_value[i] = line[start + i];
		++i;
	}
	new_value[i] = '\0';
	return (new_value);
}

char	*separate_value(char *line)
{
	char	*new_value;
	int		start;

	if (!line)
		return (NULL);
	start = 0;
	while (line[start] && line[start] != '=')
		++start;
	if (line[start] == '=')
	{
		if (line[start + 1] == '\0')
		{
			new_value = (char *)malloc(sizeof(char) * (1));
			if (!new_value)
				return (NULL);
			new_value[0] = '\0';
			return (new_value);
		}
		else
			++start;
	}
	else if (line[start] == '\0')
		return (NULL);
	new_value = separate_value_norm(line, start);
	return (new_value);
}
