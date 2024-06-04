/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:35:59 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/16 11:35:59 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*clean_data(t_data *data)
{
	free_arr(data->env);
	free_arr(data->export);
	free(data->old_work_dir);
	free(data->work_dir);
	free(data->input);
	free(data->childes_pid);
	clean_tokens(data->tokens);
	clean_commands(data->commands);
	fill_data_with_null(data);
	return (NULL);
}
