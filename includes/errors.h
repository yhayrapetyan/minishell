/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:39:11 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/16 11:39:11 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define WAIT_ERR 			"Waitpid Failed\n"
# define MALLOC_ERR 		"Allocation Failed\n"
# define ARG_ERR			"Invalid number of arguments\n"
# define WRT_PERM_ERR		"No write permission\n"
# define FILE_OPEN_ERR		"Can't open the file\n"
# define PIPE_CLOSE_ERR		"Can't close the pipe\n"
# define PIPE_CREATE_ERR	"Can't create the pipe\n"
# define FORK_CREATE_ERR	"Can't create the child process\n"
# define DUP_ERR			"Can't duplicate the descriptor\n"
# define EXEC_ERR			"Can't execute the command\n"
# define CMD_NOT_FOUND_ERR	"Command not found\n"
# define ENV_INIT_ERR		"Can't init env\n"
# define EXPORT_INIT_ERR	"Can't init export\n"
# define WDIR_INIT_ERR 		"Can't init work dir\n"
# define RLINE_ERR			"Can't read from readline()\n"
# define SQUOTE_ERR			"Unexpected EOF while looking for matching '\n"
# define DQUOTE_ERR			"Unexpected EOF while looking for matching \"\n"
# define SYNTAX_ERR			"syntax error near unexpected token"

//syntax err exit status 2
# define WAIT_STAT 			2
# define MALLOC_STAT 		3
# define ARG_STAT			4
# define WRT_PERM_STAT		1
# define FILE_OPEN_STAT		6
# define PIPE_CLOSE_STAT	7
# define PIPE_CREATE_STAT	8
# define FORK_CREATE_STAT	9
# define DUP_STAT			10
# define ENV_INIT_STAT		11
# define EXPORT_INIT_STAT	12
# define WDIR_INIT_STAT		13
# define RLINE_STAT			14
# define SQUOTE_STAT		15
# define DQUOTE_STAT		16
# define EXEC_STAT			126
# define CMD_NOT_FOUND_STAT	127

#endif
