/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:03:38 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/06/10 13:42:48 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* PARSING */
int			parse_heredoc(t_data *data, t_command **commands, t_token **tokens);
int			read_heredoc(t_io_fds *io, t_data *data, t_command *cmd);
int			create_echo_args(t_token **tokens, t_command *last_cmd);
int			add_echo_args(t_token **tokens, t_command *last_cmd);
int			fill_args(t_token **tokens, t_command *last_command);
int			parse_append(t_command **commands, t_token **tokens);
int			parse_input(t_command **commands, t_token **tokens);
int			parse_trunc(t_command **commands, t_token **tokens);
int			parse_word(t_command **commands, t_token **tokens);
int			parse_pipe(t_command **commands, t_token **tokens);
int			create_args(t_token **tokens, t_command *lst_cmd);
int			add_args(t_token **tokens, t_command *lst_cmd);
int			remove_old_ref(t_io_fds *io, int flag);
int			remove_empty_var(t_token **tokens);
int			count_echo_args(t_token *temp);
int			is_valid_filename(char *str);

#endif