/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:40:16 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:31:43 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "colors.h"//maybe need to delete

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# ifndef MINISHELL
#  define MINISHELL RED"msh$"RESET_COLOR
# endif

#endif