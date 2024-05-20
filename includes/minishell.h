/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:32:01 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/16 16:11:47 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "errors.h"
# include "colors.h" 
# include "utils.h"
# include "lexer.h"
# include "libft.h"
# include "parsing.h"
# include "expansion.h"
# include "tokenization.h"
# include "get_next_line.h"

/* HELPERS */
char	*strjoin_and_free(char const *s1, char const *s2);
void	ft_error(char *message, int status);
void	*clean_data(t_data *data);
char	**ft_arrdup(char **env);
void	print_arr(char **arr);
void	*free_arr(char **str);

#endif
