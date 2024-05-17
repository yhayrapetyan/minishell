#include "minishell.h"

int	set_status(char ch, int status)
{
	if (ch == '\'' && status == DEFAULT)
		status = IN_SQUOTE;
	else if (ch == '\"' && status == DEFAULT)
		status = IN_DQUOTE;
	else if (ch == '\'' && status == IN_SQUOTE)
		status = DEFAULT;
	else if (ch == '\"' && status == IN_DQUOTE)
		status = DEFAULT;
	return (status);
}

int is_separator(char *str, int i)
{
	if (is_white_space(str[i]))
		return (SPACES);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '<')
		return (INPUT);
	else if (str[i] == '>')
		return (TRUNC);
	else if (str[i] == '\0')
		return (END);
	else
		return (0);
}
