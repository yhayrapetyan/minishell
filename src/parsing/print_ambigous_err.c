#include "minishell.h"

int print_ambigous_err(char *orig_name)
{
	char	*temp;
	char	*message;

	temp = ft_strjoin(PROG_NAME, orig_name);
	if (!temp)
		return (0);
	message = ft_strjoin(temp, ": ");
	free(temp);
	if (!message)
		return (0);
	temp = ft_strjoin(message, AMBIGOUS_REDIR_ERR);
	free(message);
	if (!temp)
		return (0);
	write(2, temp, ft_strlen(temp));//attention
	free(temp);
	return (1);
}