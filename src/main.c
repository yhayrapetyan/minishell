/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:31:03 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/13 12:51:21 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_minishell(t_data *data)
{
	char 	*temp;

	while (1)
	{
		temp = readline(MINISHELL);
		add_history(temp);
		data->input = ft_strtrim(temp, " \t\f\r\v");//maybe more
		free(temp);
		if (ft_strcmp(data->input, "STOP") == 0)
		{
			rl_clear_history();
			break ;
		}
		printf("%s\n", data->input);
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
	clean_data(&data);

	(void)ac;
	(void)av;
	(void)env;
	return (0);
}
