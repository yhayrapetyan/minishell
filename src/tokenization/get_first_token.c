#include "minishell.h"

t_token *get_first_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->prev != NULL)
		token = token->prev;
	return (token);
}
