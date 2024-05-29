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
	data->tokens = NULL;
	data->commands = NULL;
}

int	init_io_fds(t_command	*command)
{
	if (!command)
		return (0);
	if (!command->io_fds)
	{
		command->io_fds = (t_io_fds *)malloc(sizeof(t_io_fds));
		if (!command->io_fds)
			return (0);
		command->io_fds->infile = NULL;
		command->io_fds->outfile = NULL;
		command->io_fds->delimiter = NULL;
		command->io_fds->delim_in_quotes = 0;
		command->io_fds->fd_in = -1;
		command->io_fds->fd_out = -1;
	}
	return (1);
}

int	init_work_dir(t_data *data)
{
	char	buff[PATH_MAX];
	char	*wd;

	wd = getcwd(buff, PATH_MAX);
	data->work_dir = ft_strdup(wd);
	if (!data->work_dir)
		return (0);
	if (get_env_index(data->env, "OLDPWD") != -1)
	{
		data->old_work_dir = ft_strdup(get_env_value(data->env, "OLDPWD"));
		if (!data->old_work_dir)
			return (0);
	}
	else
	{
		data->old_work_dir = ft_strdup(wd);
		if (!data->old_work_dir)
			return (0);
	}
	return (1);
}

int	g_lst_exit_status = 0;

void	init_data(t_data *data, char **env)
{
	data->env = ft_arrdup(env);//need to increment shell level or set to 1
	if (!data->env)
		ft_error(ENV_INIT_ERR, ENV_INIT_STAT);
	if (!init_export(data))
	{
		clean_data(data);
		ft_error(EXPORT_INIT_ERR, EXPORT_INIT_STAT);
	}
	if (!init_work_dir(data))
	{
		clean_data(data);
		ft_error(WDIR_INIT_ERR, WDIR_INIT_STAT);
	}
	data->childes_pid = NULL;
	data->commands_count = 0;
	data->pid = -1;
}
