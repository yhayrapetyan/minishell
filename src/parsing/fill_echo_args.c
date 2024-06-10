/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_echo_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:33:08 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/06/10 12:57:30 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create(t_token **tmp, t_command *last_cmd)
{
	int	i;

	i = 1;
	last_cmd->args[0] = ft_strdup(last_cmd->name);
	if (!last_cmd->args[0])
		return (0);
	while ((*tmp)->type == WORD || (*tmp)->type == ENV || \
		(*tmp)->type == SPACES)
	{
		if ((*tmp)->type == WORD || (*tmp)->type == ENV)
			last_cmd->args[i++] = ft_strdup((*tmp)->content);
		if (!last_cmd->args[i - 1])
			return (0);
		(*tmp) = (*tmp)->next;
	}
	last_cmd->args[i] = NULL;
	return (1);
}

int	create_echo_args(t_token **tokens, t_command *last_cmd)
{
	t_token	*tmp;
	int		nb_args;

	remove_empty_var(tokens);
	tmp = *tokens;
	nb_args = count_echo_args(tmp);
	last_cmd->args = malloc(sizeof(char *) * (nb_args + 2));
	if (!last_cmd->args)
		return (0);
	if (!create(&tmp, last_cmd))
		return (0);
	*tokens = tmp;
	return (1);
}

static char	**replace_echo_args(t_token **tokens, t_command *lst_cmd, \
		char **new_args, int len)
{
	int		i;
	t_token	*temp;

	i = -1;
	temp = *tokens;
	while (++i < len)
	{
		new_args[i] = ft_strdup(lst_cmd->args[i]);
		if (!new_args[i])
			return (free_arr(new_args));
	}
	while (temp->type == WORD || temp->type == ENV || temp->type == SPACES)
	{
		if (temp->type == WORD || temp->type == ENV)
			new_args[i++] = ft_strdup(temp->content);
		if (!new_args[i - 1])
			return (free_arr(new_args));
		temp = temp->next;
	}
	new_args[i] = NULL;
	*tokens = temp;
	return (new_args);
}

int	add_echo_args(t_token **tokens, t_command *lst_cmd)
{
	t_token	*tmp;
	int		nb_args;
	int		len;
	char	**new_args;

	remove_empty_var(tokens);
	tmp = *tokens;
	nb_args = count_echo_args(tmp);
	len = 0;
	while (lst_cmd->args[len])
		len++;
	new_args = (char **)malloc(sizeof(char *) * (nb_args + len + 1));
	if (!new_args)
		return (0);
	new_args = replace_echo_args(&tmp, lst_cmd, new_args, len);
	if (!new_args)
		return (0);
	free_arr(lst_cmd->args);
	lst_cmd->args = new_args;
	*tokens = tmp;
	return (1);
}
