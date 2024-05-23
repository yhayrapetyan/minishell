#include "minishell.h"

void	ft_error(char *message, int status)
{
	write(2, RED, 7);
	write(2, "Error\n", 6);
	write(2, YELLOW, 7);
	write(2, message, ft_strlen(message));
	write(2, RESET_COLOR, 4);
	exit(status);
}

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

int	syntax_err(char *message, char *detail, int quotes)
{
	char	*error_msg;
	char	*temp;

	error_msg = ft_strjoin(PROG_NAME, message);
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