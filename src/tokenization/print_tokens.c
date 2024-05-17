#include "minishell.h"

void	print_tokens(t_data *data)
{
	int type;
	int state;

	data->tokens = get_first_token(data->tokens);
	while (data->tokens)
	{
		type = data->tokens->type;
		state = data->tokens->state;
		printf("content = %sEOF\nlen = %d\n",
			   data->tokens->content,
			   data->tokens->len);
		if (state == 0)
			printf("state = DEFAULT\n");
		else if (state == 1)
			printf("state = IN_SQUOTES\n");
		else if (state == 2)
			printf("state = IN_DQUOTES\n");
		if (type == 1)
			printf("type = SPACES\n\n");
		else if (type == 2)
			printf("type = WORD\n\n");
		else if (type == 3)
			printf("type = ENV\n\n");
		else if (type == 4)
			printf("type = PIPE\n\n");
		else if (type == 5)
			printf("type = INPUT\n\n");
		else if (type == 6)
			printf("type = TRUNC\n\n");
		else if (type == 7)
			printf("type = HEREDOC\n\n");
		else if (type == 8)
			printf("type = APPEND\n\n");
		else if (type == 9)
			printf("type = END\n\n");

		data->tokens = data->tokens->next;
	}
}
