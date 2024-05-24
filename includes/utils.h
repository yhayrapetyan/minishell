/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:40:16 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/24 12:49:42 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "colors.h"//maybe need to delete
# include "lexer.h"//maybe need to delete

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# ifndef HEREDOC_NAME
#  define HEREDOC_NAME "heredoc"
# endif
# ifndef PROG_NAME
#  define PROG_NAME "minishell: "
# endif

# ifndef MINISHELL
#  define MINISHELL RED"msh$"RESET_COLOR
# endif

/* UTILS */
t_command	*add_command(t_command *old_command, t_command *new_command);
t_command	*get_first_command(t_command *command);
t_command	*get_last_command(t_command *command);
t_command	*empty_command(void);
int			syntax_err(char *message, char *detail, int quotes);
char		*get_env_value(char **env, char *key);
int			parse_err(char *orig_name, char *message);
int			get_env_index(char **env, char *key);
void		*clean_commands(t_command *commands);
void		ft_error(char *message, int status);
void		print_commands(t_data *data);
void		print_tokens(t_data *data);
int			get_env_len(char **env);
void		print_arr(char **arr);

#endif