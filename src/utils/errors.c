/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:55:47 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/24 13:55:47 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *message, int status)
{
	write(2, RED, 7);
	write(2, "Error\n", 6);
	write(2, YELLOW, 7);
	write(2, message, ft_strlen(message));
	write(2, RESET_COLOR, 4);
	exit(status);
}

int	parse_err(char *orig_name, char *err_message)
{
	char	*temp;
	char	*message;

	temp = ft_strjoin(PROG_NAME, orig_name);
	if (!temp)
		return (0);
	message = ft_strjoin(temp, ": ");
	free(temp);
	if (!message)
		return (0);
	temp = ft_strjoin(message, err_message);
	free(message);
	if (!temp)
		return (0);
	write(2, temp, ft_strlen(temp));//attention
	write(2, "\n", 1);
	free(temp);
	return (1);
}

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
