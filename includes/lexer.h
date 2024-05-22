/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:29:44 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:29:44 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum s_type
{
	SPACES = 1,
	WORD,
	ENV,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
	END,
}	t_type;

typedef enum s_state
{
	DEFAULT,
	IN_SQUOTE,
	IN_DQUOTE,
}	t_state;

typedef struct s_token
{
	char			*content;
	int				len;
	t_type			type;
	t_state			state;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_io_fds
{
	char	*infile;
	char	*outfile;
	char	*delimiter;
	int		delim_in_quotes;
	int		fd_in;
	int		fd_out;
	// int		stdin_backup;
	// int		stdout_backup;
}	t_io_fds;

typedef struct s_command
{
	char				*name;
	char				*path;
	char				**args;
//	bool				pipe_output;
//	int					*pipe_fd;
	t_io_fds			*io_fds;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_data
{
	char		**env;
	char		**export;
	char		*work_dir;
	char		*old_work_dir;
	char		*input;
	t_token		*tokens;
	t_command	*commands;
}	t_data;

/* INITIALIZATION */
void		init_data(t_data *data, char **env);
void		fill_data_with_null(t_data *data);
int			init_io_fds(t_command	*command);
int			init_work_dir(t_data *data);
int			init_export(t_data *data);
void		sort_arr(char **arr);

/* ENV */
char		*get_env_value(char **env, char *key);
int			get_env_index(char **env, char *key);
int			get_env_len(char **env);

/* LEXER */
int			syntax_err(char *message, char *detail, int quotes);
int			check_separators_consecutive(t_token *tokens);
void		*clean_commands(t_command *commands);//mv to init
int			remove_quotes(t_token **tokens);
int			handle_quotes(t_data *data);
int			is_white_space(char ch);
int			lexer(t_data *data);


#endif
