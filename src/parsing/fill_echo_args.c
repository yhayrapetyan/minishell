/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_echo_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:33:08 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/30 20:05:24 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_echo_args(t_token **tokens, t_command *last_cmd)
{
	t_token	*tmp;
	int		i;
	int		nb_args;

	remove_empty_var(tokens);
	tmp = *tokens;
	nb_args = count_echo_args(tmp);
	last_cmd->args = malloc(sizeof(char *) * (nb_args + 2));
	if (!last_cmd->args)
		return (0);
	i = 0;
	last_cmd->args[i++] = ft_strdup(last_cmd->name);
	if (!last_cmd->args[i - 1])
		return (0);
	while (tmp->type == WORD || tmp->type == ENV)
	{
		if (tmp->join == 1)
			last_cmd->args[i] = join_vars(&tmp);
		else
			last_cmd->args[i] = ft_strdup(tmp->content);
		if (!last_cmd->args[i])
			return (0);
		i++;
		tmp = tmp->next;
	}
	last_cmd->args[i] = NULL;
	*tokens = tmp;
	return (1);
}

static char	**replace_echo_args(t_token **tokens, t_command *lst_cmd, \
	char **new_args, int len)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = *tokens;
	while (i < len)
	{
		new_args[i] = ft_strdup(lst_cmd->args[i]);
		if (!new_args[i])
			return (free_arr(new_args));
		i++;
	}
	while (temp->type == WORD || temp->type == ENV)
	{
		if (temp->join == 1)
			new_args[i] = join_vars(&temp);
		else
			new_args[i] = ft_strdup(temp->content);
		if (!new_args[i])
			return (free_arr(new_args));
		i++;
		temp = temp->next;
	}
	new_args[i] = NULL;
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
	new_args = replace_echo_args(tokens, lst_cmd, new_args, len);
	if (!new_args)
		return (0);
	free_arr(lst_cmd->args);
	lst_cmd->args = new_args;
	*tokens = tmp;
	return (1);
}
