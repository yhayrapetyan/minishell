/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 13:13:52 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/12 13:14:30 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlcpy(char *dst, const char *src, int dstsize)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (dstsize != 0)
	{
		while (src[i] && (i < (dstsize - 1)))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (j);
}
