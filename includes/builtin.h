/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:29:30 by skedikia          #+#    #+#             */
/*   Updated: 2024/06/11 14:39:20 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "lexer.h"
# include "libft.h"
# include "utils.h"

# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define ERROR_VALUE -1
# define NOT_FOUND -2
# define NOT_NUMERIC_ERROR 2
# define CHAR_SIZE_COMBINATIONS 256

/*
	BUILTINS
*/
int		builtin_run(t_data *data);
int		builtin_pwd(t_data *data);
int		builtin_env(t_data *data);
int		builtin_unset(t_data *data);
int		builtin_cd(t_data *data);
int		builtin_export(t_data *data);
int		builtin_echo(t_data *data);
int		builtin_exit(t_data *data);

/*
	builtin_utils.c functions
*/
int		ft_atoi_with_check(const char *str, t_data *data);
int		split_size(char **split);
void	minishell_error(char *cmd, char *arg, char *msg);
int		find_env_variable_position(char **env, char *arg);
int		find_export_variable_position(char **export, char *arg);
void	data_sort_export(t_data *data);

/*
	export functions
*/
int		update_env_variables(t_data *data, char *key,
			char *value, char *line);
int		update_export_variables(t_data *data, char *key,
			char *value, char *line);
int		add_new_env_variable(t_data *data, char *line);
int		add_new_export_variable(t_data *data, char *line);
char	*create_env_variable(char *key, char *value);
char	*create_export_variable(char *key, char *value);
int		builtin_export_validation(char *arg);
char	*separate_key(char *line);
char	*separate_value(char *line);
int		add_to_enviroment(t_data *data, char *key, char *value);

/*
	cd functions
*/
int		builtin_cd_validation(t_data *data);
char	*get_value_from_env(char **env, char *key);
int		cd_update_env_values(t_data *data);
int		cd_update_export_values(t_data *data);
int		cd_update_workdirs(t_data *data, char *new_path);
int		change_directory(t_data *data, char *arg);

/*
	exit functions
*/
int		builtin_exit_validation(char *arg,t_data *data);

/*
	unset functions
*/
int		delete_variable(t_data *data, char *arg);

#endif
