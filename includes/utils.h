/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:40:16 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/06/21 18:11:42 by yuhayrap         ###   ########.fr       */
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
# include <signal.h>
# include <sys/wait.h>
# include <termios.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "colors.h"
# include "lexer.h"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

//need to change to /tmp/.minishell_heredoc_
# ifndef HEREDOC_NAME
#  define HEREDOC_NAME ".minishell_heredoc_"
# endif
# ifndef PROG_NAME
#  define PROG_NAME "minishell: "
# endif

# ifndef PROMPT
#  define PROMPT "msh$"
# endif

extern int	g_exit_status;

/* UTILS */
t_command	*add_command(t_command *old_command, t_command *new_command);
t_command	*get_first_command(t_command *command);
t_command	*get_last_command(t_command *command);
t_command	*empty_command(void);
char		*syntax_err(char *message, char *detail, int quotes);
char		*parse_err(char *orig_name, char *message);
char		*get_env_value(char **env, char *key);
int			get_env_index(char **env, char *key);
void		*clean_commands(t_command *commands);
void		ft_error(char *message, int status);
void		signal_print_newline(int signal);
void		set_signals_noninteractive(void);
void		set_signals_interactive(void);
void		start_minishell(t_data *data);
void		signal_reset_prompt(int sig);
void		system_errors(int status);
int			get_env_len(char **env);
void		print_arr(char **arr);
void		disable_echoctl(void);
void		ignore_sigquit(void);

#endif