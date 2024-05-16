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
	SPACES,
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
int		tokenization(t_data *data);
int		lexer(t_data *data);

#endif