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



int	main(int ac, char **av, char **env)
{
	t_data	data;

	data.env = ft_arrdup(env);
	data.export = get_export(data.env);
	int i = 0;
	while (data.env[i])
	{
		printf("%s\n", data.env[i]);
		i++;
	}
	printf("\n\n\n");
	i = 0;
	while (data.export[i])
	{
		printf("%s\n", data.export[i]);
		i++;
	}
	free_arr(data.env);
	free_arr(data.export);
	(void)ac;
	(void)av;
	(void)env;
	return (0);
}
