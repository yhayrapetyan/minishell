#include "minishell.h"

static int	check_command_access(char **bin_paths, t_command *cmd)
{
	char	*cmd_path;
	char	*temp;
	int		i;

	i = 0;
	while (bin_paths[i])
	{
		temp = ft_strjoin(bin_paths[i], "/");
		if (temp == NULL)
			return (-1);
		cmd_path = ft_strjoin(temp,cmd->name);
		free(temp);
		if (cmd_path == NULL)
			return (-1);
		if (access(cmd_path, F_OK) == 0)
		{
			cmd->path = cmd_path;
			return (1);
		}
		free(cmd_path);
		i++;
	}
	return (1);
}

static int	get_bin_path(t_data *data, t_command *cmd)
{
	char	**bin_paths;
	int		i;
	int 	status;

	i = get_env_index(data->env, "PATH");
	bin_paths = ft_split(data->env[i] + 5, ':');
	if (bin_paths == NULL)
		return (-1);
	status = check_command_access(bin_paths, cmd);
	free_arr(bin_paths);
	return (status);
}

static int	get_path_with_env(t_data *data, t_command *cmd)
{
	int status;

	status = 1;
	if (ft_strncmp(cmd->name, "./", 2) == 0 || ft_strncmp(cmd->name, "/", 1) == 0)
	{
		cmd->path = ft_strdup(cmd->name);
		if (!cmd->path)
			return (-1);
	}
	else
		status = get_bin_path(data, cmd);
	if (status < 1)
		return (status);
	if (cmd->path == NULL && is_relative_path(cmd->name) && \
		access(cmd->name, F_OK) == 0)
	{
		cmd->path = ft_strdup(cmd->name);
		if (!cmd->path)
			return (-1);
	}
	return (1);
}

int	get_path(t_data *data, t_command *cmd)
{
	int 	status;

	if (!cmd->name)
		return (1);//fix
//	status = is_builtin(cmd->name);
//	if (status == 1)
//		printf("OUR BUILTIN\n");//need to handle our builtin
//	else if (status == -1)
//		ft_error("NOT our problem :-)\n", 111);//need to change error handling
	status = 1;
	if (get_env_index(data->env, "PATH") != -1)
		status = get_path_with_env(data, cmd);
	else
	{
		if ((ft_strncmp(cmd->name, "./", 2) == 0  || ft_strncmp(cmd->name, "/", 1) ) && \
			access(cmd->name, F_OK) == 0)
		{
			cmd->path = ft_strdup(cmd->name);
			if (!cmd->path)
				return (-1);
		}
		else if (access(cmd->name, F_OK) == 0)
		{
			cmd->path = ft_strdup(cmd->name);
			if (!cmd->path)
				return (-1);
		}
	}
	return (status);
}