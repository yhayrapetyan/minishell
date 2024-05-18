#include "minishell.h"

static int	invalid_consecutive(t_token *token)
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
		return (syntax_err(SYNTAX_ERR, tokens->content, 1));
	while (tokens)
	{
		if (invalid_consecutive(tokens))
		{
			if (tokens->type == END && tokens->prev && tokens->prev->type > PIPE)
				return (syntax_err(SYNTAX_ERR, "newline", 1));
			else if (tokens->type == END && tokens->prev)
				return (syntax_err(SYNTAX_ERR, tokens->prev->content, 1));
			else
				return (syntax_err(SYNTAX_ERR, tokens->content, 1));
		}
		tokens = tokens->next;
	}
	return (1);
}
