/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:03:38 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 20:44:56 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* PARSING */
t_command	*add_command(t_command *old_command, t_command *new_command);
int			parse_heredoc(t_data *data, t_command **commands, t_token **tokens);
int			fill_args(t_token **tokens, t_command *last_command);
int			parse_append(t_command **commands, t_token **tokens);
int			parse_input(t_command **commands, t_token **tokens);
int			parse_trunc(t_command **commands, t_token **tokens);
int			parse_word(t_command **commands, t_token **tokens);
int			parse_pipe(t_command **commands, t_token **tokens);
int 		read_heredoc(t_io_fds *io, t_data *data);
t_command	*get_first_command(t_command *command);
int			remove_old_ref(t_io_fds *io, int flag);
t_command	*get_last_command(t_command *command);
int 		print_ambigous_err(char *orig_name);
int			create_commands(t_data *data);
int 		is_valid_filename(char *str);
t_command	*empty_command(void);

#endif