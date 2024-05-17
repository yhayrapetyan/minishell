/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:04:18 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/16 16:27:45 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_input_empty(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		if (!is_white_space(data->input[i]))
			return (0);
		i++;
	}
	return (1);
}

static void update_var_node_type(t_token **tokens)
{
	int 	i;
	t_token *temp;

	if (!tokens)
		return ;
	*tokens = get_first_token(*tokens);
	temp = *tokens;
	while ((*tokens))
	{
		i = 0;
		while ((*tokens)->content[i])
		{
			if ((*tokens)->content[i] == '$')
			{
				if ((*tokens)->prev && (*tokens)->prev->type == HEREDOC)
					break ;
				(*tokens)->type = ENV;
			}
			i++;
		}
		(*tokens) = (*tokens)->next;
	}
	*tokens = temp;
}

/* returns
 * 1 => success
 * -1 => malloc_err
 * -2 => dquote_err
 * -3 => squote_err
 * -4 => readline_err
 * -5 => syntax_err [separators_consecutive]
 * */
int	lexer(t_data *data)
{
	int status;

	status = 0;
	if (data->input == NULL)
		return (-4);
	if (is_input_empty(data))//if input = '\0' someone throw error?
		return (1);
	add_history(data->input);
	status = tokenization(data);
	if (status < 1)
		return (status);
	if (data->tokens->type == END)
		return (-11);//idk steal about this
	update_var_node_type(&data->tokens);//need to find better name
	status = check_separators_consecutive(data->tokens);
	if (status < 1)
		return (-5);
	print_tokens(data);
	return (1);
}
