#include "minishell.h"

static int have_quotes(char *content)
{
	int i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '"' || content[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int handle_quotes(t_data *data)
{
	t_token *temp;

	temp = data->tokens;
	while (temp)
	{
		if (have_quotes(temp->content) &&\
			(!temp->prev || (temp->prev && temp->prev->type != HEREDOC)))
		{
			if (!remove_quotes(&temp))
				return (-1);
		}
		temp = temp->next;
	}
	return (1);
}
