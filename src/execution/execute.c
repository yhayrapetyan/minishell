#include "minishell.h"

int	execute_command(t_data *data, t_command *cmd)
{
	int	status;

	if (cmd->err_message)
	{
		printf("%s\n", cmd->err_message);
		exit(cmd->err_type * (-1));//fix
	}
	status = handle_descriptors(cmd);
	if (status < 1)
		exit(status * (-1));//fix
	status = get_path(data, cmd);
	if (status < 1)
		exit(status * (-1));
	if (cmd->path == NULL)
	{
		printf("COMMAND NOT FOUND\n");
		exit(113);
	}
	if (execve(cmd->path, cmd->args, data->env) == -1)
	{
		printf("execve => %s\n", strerror(errno));
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
		exit(status * -1);//fix
	status = create_processes(data);
	if (status < 0)
		exit(status * -1);//fix
	return (status);
}
