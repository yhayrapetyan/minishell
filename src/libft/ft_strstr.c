/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:54:21 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/06/10 12:54:21 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	substring_len(char *search_in, char *to_find)
{
	int	i;

	i = 0;
	while (to_find[i] != '\0')
	{
		if (search_in[i] != to_find[i])
			return (0);
		i++;
	}
	return (i);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;

	i = 0;
	if (to_find[i] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		if (str[i] == to_find[0])
		{
			if (substring_len(str + i, to_find))
				return (str + i);
		}
		i++;
	}
	return (NULL);
}
