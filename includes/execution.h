/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:43:21 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/31 12:43:21 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

/* EXECUTION */
int		close_pipes(t_command *cmd, t_command *exception);
int		get_exit_status(int err_type, char *err_message);
int		execute_command(t_data *data, t_command *cmd);
int		get_path(t_data *data, t_command *cmd);
int		handle_descriptors(t_command *cmd);
int		is_relative_path(char *cmd_name);
int		reset_descriptors(t_io_fds *io);
int		create_processes(t_data *data);
int		create_pipes(t_data *data);
int		is_builtin(char *cmd);
int		execute(t_data *data);

#endif
