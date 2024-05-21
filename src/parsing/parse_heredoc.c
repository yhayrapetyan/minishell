/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:41:27 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 21:28:54 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*gnerate_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*number;

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, number);
	free(number);
	i++;
	return (name);
}

static char	*get_delimiter(char *delim)
{
	int	len;

	len = ft_strlen(delim) - 1;
	if ((delim[0] == '\"' && delim[len] == '\"')
		|| (delim[0] == '\'' && delim[len] == '\''))
	{
		// *quotes = true;
		return (ft_strtrim(delim, "\'\""));//fix
	}
	return (ft_strdup(delim));
}

int	parse_heredoc(t_data *data, t_command **commands, t_token **tokens)
{
	t_token		*tmp;
	t_command	*lst_cmd;
	t_io_fds	*io;

	tmp = *tokens;
	lst_cmd = get_last_command(*commands);
	if (!init_io_fds(lst_cmd))
		return (0);
	io = lst_cmd->io_fds;
	if (!remove_old_ref(io, 1))
		return (1);
	io->infile = generate_heredoc_name();
	if (!io->infile)
		return (0);
	io->delimiter = get_delimiter(temp->next->content);
	(void)data;
	(void)commands;
	(void)tokens;
	return (1);
}
