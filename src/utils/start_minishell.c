/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:03:00 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/31 13:03:00 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_loop(t_data *data)
{
	free(data->input);
	free(data->childes_pid);
	clean_tokens(data->tokens);
	clean_commands(data->commands);
	data->input = NULL;
	data->tokens = NULL;
	data->commands = NULL;
	data->childes_pid = NULL;
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
 * -12 => here-document delimited by end-of-file
 * */
void	start_minishell(t_data *data)
{
	int	status;

	while (1)
	{
//		set_signals_interactive();
		data->input = readline(RED PROMPT RESET_COLOR);
//		set_signals_noninteractive();
		if (!data->input)
		{
			clean_data(data);
			builtin_exit(data);
		}
		status = lexer(data);
		if (status > -5 && status < 0)
		{
			clean_data(data);
			system_errors(status);
		}
		g_exit_status = execute(data);
		if (g_exit_status < 0)
		{
			clean_data(data);
			system_errors(g_exit_status);
		}
		clean_loop(data);
	}
}
