/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:16:05 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:16:05 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

/* TOKENIZATION */
t_token		*add_token(t_token *token, char **content, int type, int state);
int			save_separator(t_data *data, int index, int type);
t_token		*create_token(char **content, int type, int state);
int			save_token(t_data *data, int start, int *end);
int			save_word(t_data *data, int start, int end);
t_token		*get_first_token(t_token *token);
int			set_state(char ch, int status);
int			is_separator(char *str, int i);
void		*clean_tokens(t_token *tokens);
void		print_tokens(t_data *data);
int			tokenization(t_data *data);

#endif
