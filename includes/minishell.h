/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:32:01 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/16 11:41:30 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "errors.h"
# include "colors.h"
# include "utils.h"

/* LIBFT */
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
int		ft_strlcpy(char *dst, const char *src, int dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *s1);
int		ft_strlen(const char *s);

/* HELPERS */
char	*strjoin_and_free(char const *s1, char const *s2);
void	ft_error(char *message, int status);
void	init_data(t_data *data, char **env);
void	fill_data_with_null(t_data *data);
int		init_work_dir(t_data *data);
int		init_export(t_data *data);
void	*clean_data(t_data *data);
void	sort_arr(char **export);
char	**ft_arrdup(char **env);
void	print_arr(char **arr);
void	*free_arr(char **str);

/* ENV */
char	*get_env_value(char **env, char *key);
int		get_env_index(char **env, char *key);
int		get_env_len(char **env);

#endif
