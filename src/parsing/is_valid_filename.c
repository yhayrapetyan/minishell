#include "minishell.h"

/* need for ambigous redirection err */
int is_valid_filename(char *str)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (str[i] && is_white_space(str[i]))//maybe just space
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (is_white_space(str[i]))
			flag = 1;
		else
		{
			if (flag == 1)
				return (0);
		}
		i++;
	}
	return (1);
}
