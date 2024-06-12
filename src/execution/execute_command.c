/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:50:54 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/06/10 12:50:54 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* idk how to name this function */
static void	exit_helper(char *cmd_name, char *err_message, t_data *data)
{
	char	*err_msg;
	if (ft_strstr(err_message, "Permission denied") != NULL)
	{
		if (access(cmd_name, F_OK) == 0 && access(cmd_name, X_OK) == 0)
			err_msg = parse_err(cmd_name, "Is a directory");
		else
			err_msg = parse_err(cmd_name, err_message);
	}
	else
		err_msg = parse_err(cmd_name, err_message);
	if (!err_msg)
		exit (1);
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
	if (ft_strstr(err_msg, "Permission denied") != NULL || \
		ft_strstr(err_msg, "Is a directory") != NULL)
	{
		free(err_msg);
		exit(PERMISSION_STAT);
	}
	free(err_msg);
	clean_data(data);//check
	exit(CMD_NOT_FOUND_STAT);
}

static void	handle_error(t_data *data, t_command *cmd)
{
	int	exit_status;

	write(2, cmd->err_message, ft_strlen(cmd->err_message));
	write(2, "\n", 1);
	exit_status = get_exit_status(cmd->err_type, cmd->err_message);
	clean_data(data);
	exit(exit_status);
}

static void	handle_builtin(t_data *data, t_command *cmd)
{
	data->commands = cmd;
	builtin_run(data);
	clean_data(data);
	exit(g_exit_status);
}

int	execute_command(t_data *data, t_command *cmd)
{
	int		status;

	if (cmd->err_message)
		handle_error(data, cmd);
	status = handle_descriptors(cmd);
	if (status < 1)
		exit(1);
	if (is_builtin(cmd->name))
		handle_builtin(data, cmd);
	if (cmd->name == NULL)
	{
		if (cmd->is_input_heredoc)
			unlink(cmd->io_fds->infile);
		clean_data(data);
		exit(0);
	}
	status = get_path(data, cmd);
	if (status < 1)
		exit(1);
	if (cmd->path == NULL)
		exit_helper(cmd->name, CMD_NOT_FOUND_ERR, data);
	if (execve(cmd->path, cmd->args, data->env) == -1)
		exit_helper(cmd->name, strerror(errno), data);
	return (1);
}
