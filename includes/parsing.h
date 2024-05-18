/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:03:38 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/16 16:28:41 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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

typedef struct s_data
{
	char	**env;
	char	**export;
	char	*work_dir;
	char	*old_work_dir;
	char	*input;
	t_token *tokens;
}	t_data;

/* INITIALIZATION */
void	init_data(t_data *data, char **env);
void	fill_data_with_null(t_data *data);
int		init_work_dir(t_data *data);
int		init_export(t_data *data);
void	sort_arr(char **arr);


/* ENV */
char	*get_env_value(char **env, char *key);
int		get_env_index(char **env, char *key);
int		get_env_len(char **env);

/* LEXER */
int 	check_separators_consecutive(t_token *tokens);
int		lexer(t_data *data);
int		is_white_space(char ch);

/* TOKENIZATION */
t_token	*add_token(t_token *token, char *content, int type, int state);
int		save_separator(t_data *data, int index, int type);
t_token	*create_token(char *content, int type, int state);
int 	save_token(t_data *data, int start, int *end);
int		save_word(t_data *data, int start, int end);
t_token *get_first_token(t_token *token);
int		set_status(char ch, int status);
int 	is_separator(char *str, int i);
void	*clean_tokens(t_token *tokens);
void	print_tokens(t_data *data);
int		tokenization(t_data *data);



#endif