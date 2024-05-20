#include "minishell.h"

int create_commands(t_data *data)
{
	t_token	*temp;
	int 	status;

	temp = data->tokens;
	while (temp && temp->next)
	{
		if (!temp->prev)
			data->commands = add_command(data->commands, empty_command());//need to check if allocation failed
		if (temp->type == WORD || temp->type == ENV)
			status = parse_word(&data->commands, &temp);
		else if (temp->type == PIPE)
			status = parse_pipe(&data->commands, &temp);
//		else if (temp->type == INPUT)
//			status = parse_input(&data->commands, &temp);
//		else if (temp->type == TRUNC)
//			status = parse_trunc(&data->commands, &temp);
//		else if (temp->type == HEREDOC)
//			status = parse_heredoc(data, &data->commands, &temp);
//		else if (temp->type == APPEND)
//			status = parse_append(&data->commands, &temp);

//		else if (temp->type == END)
//			break ;
		if (!status)
			return (-1);
	}
	return (1);
}
