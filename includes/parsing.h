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
int		syntax_err(char *message, char *detail, int quotes);
int 	check_separators_consecutive(t_token *tokens);
int 	remove_quotes(t_token **tokens);
int 	handle_quotes(t_data *data);
int		is_white_space(char ch);
int		lexer(t_data *data);

/* EXPANSION */
int		replace_old_content(t_token **tokens, char *var_value, int index);
int 	erase_variable(t_token **token, char *content, int index);
int		update_content(t_data *data, char *var_value, int i);
char	*get_variable_value(t_data *data, char *str);
void	update_state(t_token **token, char ch);
void 	update_env_token_type(t_token **tokens);
int		is_valid_variable(t_data *data, int i);
int		expand_variables(t_data *data);
int		get_var_key_len(char *str);
int 	get_var_len(char *str);

/* TOKENIZATION */
t_token	*add_token(t_token *token, char **content, int type, int state);
int		save_separator(t_data *data, int index, int type);
t_token	*create_token(char **content, int type, int state);
int 	save_token(t_data *data, int start, int *end);
int		save_word(t_data *data, int start, int end);
t_token *get_first_token(t_token *token);
int		set_state(char ch, int status);
int 	is_separator(char *str, int i);
void	*clean_tokens(t_token *tokens);
void	print_tokens(t_data *data);
int		tokenization(t_data *data);



#endif