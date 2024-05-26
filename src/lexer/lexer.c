/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:04:18 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/26 12:32:21 by yuhayrap         ###   ########.fr       */
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

/* returns
 * 1 => success
 * -1 => malloc_err
 * -2 => dquote_err
 * -3 => squote_err
 * -4 => readline_err
 * -5 => syntax_err [separators_consecutive]
 * -6 => ambigous redirect
 * -7 => open err
 * */
int	lexer(t_data *data)
{
	int	status;

	if (data->input == NULL)
		return (-4);
	if (is_input_empty(data))
		return (1);
//	add_history(data->input);
	status = tokenization(data);
	if (status < 1)
		return (status);
	update_env_token_type(&data->tokens);
	prepare_for_ambiguous(data);
	status = expand_variables(data);
	if (status < 1)
		return (status);
	status = handle_quotes(data);
	if (status < 1)
		return (status);
	status = create_commands(data);
	if (status < 1)
		return (status);
	print_tokens(data);
	print_commands(data);
	return (1);
}
