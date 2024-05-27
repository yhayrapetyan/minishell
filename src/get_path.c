#include "minishell.h"

char	*check_command_access(char **bin_paths, char *cmd)
{
	char	*cmd_path;
	char	*temp;
	int		i;

	i = 0;
	while (bin_paths[i])
	{
		temp = ft_strjoin(bin_paths[i], "/");
		if (temp == NULL)
			return (NULL);//malloc err
		cmd_path = ft_strjoin(temp,cmd);
		free(temp);
		if (cmd_path == NULL)
			return (NULL);//malloc err
		if (access(cmd_path, F_OK) == 0)// maybe we should also check permission
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	*get_bin_path(t_data *data, char *cmd)
{
	char	*command_path;
	char	**bin_paths;
	int		i;

	i = get_env_index(data->env, "PATH");
	bin_paths = ft_split(data->env[i] + 5, ':');
	if (bin_paths == NULL)
		return (NULL);//malloc err
	command_path = check_command_access(bin_paths, cmd);
	free_arr(bin_paths);
	return (command_path);
}

char	*get_path_with_env(t_data *data, char *cmd)
{
	char	*path;

	path = NULL;
	if (ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "/", 1) == 0)
	{
		path = ft_strdup(cmd);
		if (!path)
			return (NULL);//malloc err
	}
	else
		path = get_bin_path(data, cmd);
	if (path == NULL && is_relative_path(cmd) && \
		access(cmd, F_OK) == 0)
	{
		path = ft_strdup(cmd);
		if (!path)
			return (NULL);//malloc err
	}
	return (path);
}

char	*get_path(t_data *data, char *cmd)
{
	char	*path;
	int 	status;

	path = NULL;
	status = is_builtin(cmd);
	if (status == 1)
		printf("OUR BUILTIN\n");//need to handle our builtin
	else if (status == -1)
		ft_error("NOT our problem :-)\n", 111);//need to change error handling
	if (get_env_index(data->env, "PATH") != -1)
		path = get_path_with_env(data, cmd);
	else
	{
		if ((ft_strncmp(cmd, "./", 2) == 0  || ft_strncmp(cmd, "/", 1) ) && \
			access(cmd, F_OK) == 0)
		{
			path = ft_strdup(cmd);
			if (!path)
				return (NULL);//malloc err
		}
		else if (access(cmd, F_OK) == 0)
		{
			path = ft_strdup(cmd);
			if (!path)
				return (NULL);//malloc err
		}
	}
	//need to check path null because it's not found or malloc err if not malloc err and path == NULL error => command not found
	return (path);
}