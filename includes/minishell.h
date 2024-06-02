/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:32:01 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/24 17:37:41 by yuhayrap         ###   ########.fr       */
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

# include "builtin.h"

/* HELPERS */
char	*strjoin_and_free(char const *s1, char const *s2);
char	**ft_arrdup(char **env);
int		is_white_space(char ch);
char	*arr_join(char ***arr);
void	*free_arr(char **str);
void	sort_arr(char **arr);

#endif
