#include "minishell.h"

static void	clean_loop(t_data *data)
{
	free(data->input);
	clean_tokens(data->tokens);
	clean_commands(data->commands);
	data->input = NULL;
	data->tokens = NULL;
	data->commands = NULL;
}

/*
 * -1 	=> malloc_err
 * -2 	=> dquote_err
 * -3 	=> squote_err
 * -4 	=> readline_err
 * -5 	=> syntax_err [separators_consecutive]
 * -6 	=> ambigous redirect
 * -7 	=> open err
 * -8 	=> pipe err
 * -9 	=> fork err
 * -10	=> dup2 err
 * -11 => waitpid err
 * */
void	start_minishell(t_data *data)
{
	int	status;

	while (1)
	{
		// data->input = readline(MINISHELL);
		data->input = get_next_line(0);
		data->input[ft_strlen(data->input) - 1] = '\0';//temp solution for need for checking memory leaks
		if (ft_strcmp(data->input, "exit") == 0)
			break ;
		status = lexer(data);
		if (status > -5 && status < 0)
		{
			clean_data(data);
			system_errors(status);
		}
//		printf("%s\n", data->input);
		g_lst_exit_status = execute(data);
		printf("exit status = %d\n", g_lst_exit_status);
		if (g_lst_exit_status < 0)
		{
			clean_data(data);
			system_errors(g_lst_exit_status);
		}
		clean_loop(data);
	}
}
