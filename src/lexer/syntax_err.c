/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:24:35 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:24:35 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_err(char *message, char *detail, int quotes)
{
	char	*error_msg;
	char	*temp;

	error_msg = ft_strjoin(PROG_NAME, message);
	if (!error_msg)
		return (-1);
	if (quotes)
		temp = ft_strjoin(error_msg, " `");
	else
		temp = ft_strjoin(error_msg, ": ");
	free(error_msg);
	if (!temp)
		return (-1);
	error_msg = temp;
	temp = ft_strjoin(error_msg, detail);
	free(error_msg);
	if (!temp)
		return (-1);
	error_msg = temp;
	if (quotes)
		temp = ft_strjoin(error_msg, "'");
	free(error_msg);
	if (!temp)
		return (-1);
	error_msg = temp;
	printf("%s\n", error_msg);//need change to write in stderr_fileno
	free(error_msg);
	return (-5);
}
