#include "minishell.h"

int parse_pipe(t_command **commands, t_token **tokens)
{
	t_command	*last_command;
	t_command	*temp;

	last_command = get_last_command(*commands);
//	last_command->pipe_output = 1;
	temp = add_command(last_command, empty_command());
	if (!temp)
		return (0);
	*commands = temp;
	*tokens = (*tokens)->next;
	return (1);
}
