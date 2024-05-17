/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:31:03 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/16 15:21:18 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_minishell(t_data *data)
{

	while (1)
	{
		data->input = readline(MINISHELL);
		if (ft_strcmp(data->input, "exit") == 0)
			break ;
		if (lexer(data) < 1)
		{
			clean_data(data);
			rl_clear_history();
			exit(21);//need to handle error print
		}
//		printf("%s\n", data->input);
		free(data->input);
		data->input = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	fill_data_with_null(&data);
	init_data(&data, env);
	start_minishell(&data);
	// print_arr(data.export);
	clean_data(&data);
	(void)ac;
	(void)av;
	(void)env;
	return (0);
}
