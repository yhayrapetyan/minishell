#include "minishell.h"

static int swap(char **tmp,char **str, char ***arr)
{
	if (!*tmp)
	{
		free(*str);
		free_arr(*arr);
		return (0);
	}
	free(*str);
	*str = *tmp;
	return (1);
}

char	*arr_join(char ***arr)
{
	char	*tmp;
	char	*res;
	int 	i;

	i = 1;
	res = ft_strdup((*arr)[0]);
	if (!res)
		return (free_arr(*arr));
	while ((*arr)[i])
	{
		tmp = ft_strjoin(res, (*arr)[i]);
		if (!swap(&tmp, &res, arr))
			return (NULL);
		if ((*arr)[i + 1])
		{
			tmp = ft_strjoin(res, " ");
			if (!swap(&tmp, &res, arr))
				return (NULL);
		}
		i++;
	}
	free_arr(*arr);
	return (res);
}