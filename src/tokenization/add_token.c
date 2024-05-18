#include "minishell.h"

t_token	*add_token(t_token *token, char **content, int type, int state)
{
	t_token	*new_token;

	new_token = create_token(content, type, state);
	if (!new_token)
		return (NULL);
	if (!token)
		return (new_token);
	token->next = new_token;
	new_token->prev = token;
	return (new_token);
}
