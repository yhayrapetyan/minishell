#include "minishell.h"

static int	invalid_consecutives(t_token *token)
{
	if (token->prev)
	{
		if (token->type == PIPE && token->prev->type == PIPE)
			return (1);
		if (token->type > PIPE && token->prev->type > PIPE)
			return (1);
		if (token->type == END && token->prev->type >= PIPE)
			return (1);
	}
	return (0);
}

/*
 * returns
 * 1 => success
 * -1 => syntax err
 */
int check_separators_consecutive(t_token *tokens)
{
	tokens = get_first_token(tokens);
	if (tokens->type == PIPE)
		return (-1);
	while (tokens)
	{
		if (invalid_consecutives(tokens))
		{
			printf("SYNTAX ERROR\n");
			return (-1);//need to handle correct error message generation.
		}
		tokens = tokens->next;
	}
	return (1);
}