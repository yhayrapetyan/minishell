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

/*
 * -1 	=> malloc_err
 * -2 	=> dquote_err
 * -3 	=> squote_err
 * -4 	=> readline_err
 * -5 	=> syntax_err [separators_consecutive]
 * -6 	=> ambigous redirect
 * -7 	=> open err
 * -8 	=> pipe err
 * -9 	=> fork err
 * -10	=> dup2 err
 * -11 => waitpid err
 * */
void	system_errors(int status)
{
	if (status == -1)
		ft_error(MALLOC_ERR, MALLOC_STAT);
	else if (status == -2)
		ft_error(DQUOTE_ERR, DQUOTE_STAT);
	else if (status == -3)
		ft_error(SQUOTE_ERR, SQUOTE_STAT);
	else if (status == -4)
		ft_error(RLINE_ERR, RLINE_STAT);
	else if (status == -8)
		ft_error(PIPE_CREATE_ERR, PIPE_CREATE_STAT);
	else if (status == -9)
		ft_error(FORK_CREATE_ERR, FORK_CREATE_STAT);
}

char	*parse_err(char *orig_name, char *err_message)
{
	char	*temp;
	char	*message;

	temp = ft_strjoin(PROG_NAME, orig_name);
	if (!temp)
		return (NULL);
	message = ft_strjoin(temp, ": ");
	free(temp);
	if (!message)
		return (NULL);
	temp = ft_strjoin(message, err_message);
	free(message);
	if (!temp)
		return (NULL);
	return (temp);
}

/* check memory leaks*/
char	*syntax_err(char *message, char *detail, int quotes)
{
	char	*error_msg;
	char	*temp;

	error_msg = ft_strjoin(PROG_NAME, message);
	if (!error_msg)
		return (NULL);
	if (quotes)
		temp = ft_strjoin(error_msg, " `");
	else
		temp = ft_strjoin(error_msg, ": ");
	free(error_msg);
	if (!temp)
		return (NULL);
	error_msg = temp;
	temp = ft_strjoin(error_msg, detail);
	free(error_msg);
	if (!temp)
		return (NULL);
	error_msg = temp;
	if (quotes)
		temp = ft_strjoin(error_msg, "'");
	free(error_msg);
	if (!temp)
		return (NULL);
	return (temp);
}
