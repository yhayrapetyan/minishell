/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:40:16 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/16 11:41:03 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096

# endif
# ifndef MINISHELL
#  define MINISHELL "msh$"

# endif

typedef struct s_data
{
	char	**env;
	char	**export;
	char	*work_dir;
	char	*old_work_dir;
	char	*input;
	int		env_len;
}	t_data;

#endif