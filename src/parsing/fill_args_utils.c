/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:06:57 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/06/10 13:29:34 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_proper_size(t_token *token)
{
	int	i;

	i = 0;
	while (token->type == WORD || token->type == ENV || token->type == SPACES)
	{
		if (token->type == WORD || token->type == ENV)
			i++;
		token = token->next;
	}
	return (i);
}

/*
*	0 => fail
*	1 => success
*/
int	create_args(t_token **tokens, t_command *lst_cmd)
{
	t_token	*temp;
	int		i;
	int		nb;

	i = 0;
	temp = *tokens;
	nb = count_proper_size(temp);
	lst_cmd->args = (char **)malloc(sizeof(char *) * (nb + 2));
	if (!lst_cmd->args)
		return (0);
	lst_cmd->args[i++] = ft_strdup(lst_cmd->name);
	if (!lst_cmd->args[i - 1])
		return (0);
	while (temp->type == WORD || temp->type == ENV || temp->type == SPACES)
	{
		if (temp->type == WORD || temp->type == ENV)
			lst_cmd->args[i++] = ft_strdup(temp->content);
		if (!lst_cmd->args[i - 1])
			return (0);
		temp = temp->next;
	}
	lst_cmd->args[i] = NULL;
	*tokens = temp;
	return (1);
}

/*
*	NULL => fail
*	ptr => success
*/
static char	**replace_args(t_token **tokens, t_command *lst_cmd,
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
	while (temp->type == WORD || temp->type == ENV || temp->type == SPACES)
	{
		if (temp->type == WORD || temp->type == ENV)
			new_args[i++] = ft_strdup(temp->content);
		if (!new_args[i - 1])
			return (free_arr(new_args));
		temp = temp->next;
	}
	new_args[i] = NULL;
	return (new_args);
}

static int	add_args_helper(t_token **tokens, t_token **temp)
{
	int		i;

	i = 0;
	while ((*temp)->type == WORD || \
		(*temp)->type == ENV || (*temp)->type == SPACES)
	{
		if ((*temp)->type == WORD || (*temp)->type == ENV)
			i++;
		(*temp) = (*temp)->next;
	}
	return (i);
}

/*
*	0 => fail
*	1 => success
*/
int	add_args(t_token **tokens, t_command *lst_cmd)
{
	int		i;
	int		len;
	char	**new_args;
	t_token	*temp;

	temp = *tokens;
	i = add_args_helper(tokens, &temp);
	len = 0;
	while (lst_cmd->args[len])
		len++;
	new_args = (char **)malloc(sizeof(char *) * (i + len + 1));
	if (!new_args)
		return (0);
	new_args = replace_args(tokens, lst_cmd, new_args, len);
	if (!new_args)
		return (0);
	free_arr(lst_cmd->args);
	lst_cmd->args = new_args;
	*tokens = temp;
	return (1);
}
