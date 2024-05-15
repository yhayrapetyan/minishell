#include "minishell.h"

void	*clean_data(t_data *data)
{
	free_arr(data->env);
	free_arr(data->export);
	free(data->old_work_dir);
	free(data->work_dir);
	return (NULL);
}