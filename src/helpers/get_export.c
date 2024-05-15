#include "minishell.h"

static void sort_export(char **export)
{
	int 	count;
	char	*temp;
	int 	i;
	int 	j;

	count = 0;
	while (export[count] != NULL) {
		count++;
	}
	i = 0;
	while (i < count - 1) {
		j = 0;
		while (j < count - i - 1) {
			if (ft_strcmp(export[j], export[j + 1]) > 0) {
				temp = export[j];
				export[j] = export[j + 1];
				export[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static	char	*get_export_value(char **env, int i)
{
	char	*res;
	int 	len;
	int 	j;

	len = ft_strlen(env[i]);
	res = (char *)malloc(sizeof(char) * (len + 3));//for "" and \0
	if (!res)
		return (NULL);
	j = 0;
	while (env[i][j])
	{
		res[j] = env[i][j];
		if (res[j] == '=')
			break ;
		j++;
	}
	res[++j] = '"';
	j++;
	while (env[i][j])
	{
		res[j] = env[i][j];
		j++;
	}
	res[j] = '"';
	res[++j] = '\0';
	return (res);
}

char	**get_export(char **env)
{
	int		i;
	char	**res;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
		i++;
	res = (char **)malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);//maybe malloc error
	i = 0;
	while (env[i])
	{
		res[i] = ft_strjoin("declare -x ", get_export_value(env, i));
		if (!res[i])
		{
			free_arr(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	sort_export(res);
	return (res);
}
