/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:31:03 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/24 16:28:29 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_minishell(t_data *data)
{
	while (1)
	{
		// data->input = readline(MINISHELL);
		data->input = get_next_line(0);
		data->input[ft_strlen(data->input) - 1] = '\0';//temp solution for need for checking memory leaks
		if (ft_strcmp(data->input, "exit") == 0)
			break ;
		if (lexer(data) < 1)
		{
			clean_data(data);
			// rl_clear_history();
			get_next_line(-1);
			exit(21);//need to handle error print
		}
//		printf("%s\n", data->input);
		free(data->input);
		data->input = NULL;
		clean_tokens(data->tokens);
		clean_commands(data->commands);
		data->tokens = NULL;
		data->commands = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	fill_data_with_null(&data);
	init_data(&data, env);
	start_minishell(&data);
	get_next_line(-1);
	clean_data(&data);
	system("leaks minishell");
	(void)ac;
	(void)av;
	(void)env;
	return (0);
}
