#include "minishell.h"

static
int get_exit_status(int err_type)
{
	if (err_type == -5)
		return (SYNTAX_STAT);
	else if (err_type == -6)
		return (AMBIGOUS_REDIR_STAT);
	else if (err_type == -7)
		return (FILE_OPEN_STAT);
	return (0);
}

int	execute_command(t_data *data, t_command *cmd)
{
	int		status;
	char	*err_msg;

	if (cmd->err_message)
	{
		printf("%s\n", cmd->err_message);//write(2,...)
		exit(get_exit_status(cmd->err_type));
	}
	status = handle_descriptors(cmd);
	if (status < 1)
		exit(1 );//fix
	status = get_path(data, cmd);
	if (status < 1)
		exit(1);
	if (cmd->path == NULL)
	{
		err_msg = parse_err(cmd->name, CMD_NOT_FOUND_ERR);
		if (!err_msg)
			exit (1);//fix
		printf("%s", err_msg);//write(2, ...)
		exit(CMD_NOT_FOUND_STAT);
	}
	if (execve(cmd->path, cmd->args, data->env) == -1)
	{
		err_msg = parse_err(cmd->name, CMD_NOT_FOUND_ERR);
		if (!err_msg)
			exit (1);//fix
		printf("%s", err_msg);//write(2, ...)
		exit(1);//fix
	}
	return (1);
}

int execute(t_data *data)
{
	int	status;

	if (!data->commands)
		return (0);
	status = create_pipes(data);
	if (status < 1)
		return (status);
	status = create_processes(data);
	return (status);
}
