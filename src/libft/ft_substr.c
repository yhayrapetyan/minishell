/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:25:11 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:25:11 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char *s, int start, int len)
{
	char	*ch;
	int		i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	ch = (char *)malloc(sizeof(char) * (len + 1));
	if (ch == NULL)
		return (NULL);
	i = 0;
	while (i < len && (start + i) < ft_strlen(s))
	{
		ch[i] = (char)s[start + i];
		i++;
	}
	ch[i] = '\0';
	return (ch);
}
