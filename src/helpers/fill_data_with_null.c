/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_with_null.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:36:07 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/16 11:36:07 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * we are filling data with nulls, so we can
 * call clean_data() function and don't worry
 * about some undefined behavior
 */
void	fill_data_with_null(t_data *data)
{
	data->env = NULL;
	data->export = NULL;
	data->work_dir = NULL;
	data->old_work_dir = NULL;
	data->input = NULL;
}
