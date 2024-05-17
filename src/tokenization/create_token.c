#include "minishell.h"

t_token	*create_token(char *content, int type, int state)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	token->prev = NULL;
	token->content = content;
	token->type = type;
	token->state = state;
	token->len = ft_strlen(content);
	return (token);
}
