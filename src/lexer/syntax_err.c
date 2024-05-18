#include "minishell.h"

int	syntax_err(char *message, char *detail, int quotes)
{
	char	*error_msg;
	char	*temp;

	error_msg = ft_strjoin("minishell: ", message);
	if (!error_msg)
		return (-1);
	if (quotes)
		temp = ft_strjoin(error_msg, " `");
	else
		temp = ft_strjoin(error_msg, ": ");
	free(error_msg);
	if (!temp)
		return (-1);
	error_msg = temp;
	temp = ft_strjoin(error_msg, detail);
	free(error_msg);
	if (!temp)
		return (-1);
	error_msg = temp;
	if (quotes)
		temp = ft_strjoin(error_msg, "'");
	free(error_msg);
	if (!temp)
		return (-1);
	error_msg = temp;
	printf("%s\n", error_msg);//need change to write in stderr_fileno
	free(error_msg);
	return (-5);
}
