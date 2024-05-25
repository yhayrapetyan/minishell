/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <yuhayrap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:15:32 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/05/21 14:15:32 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

/* EXPANSION */
int			replace_old_content(t_token **tokens, char *var_value, int index);
int			erase_variable(t_token **token, char *content, int index);
int			update_content(t_data *data, char *var_value, int i);
char		*get_variable_value(t_data *data, char *str);
char		*expand_heredoc(t_data *data, char *line);
void		update_env_token_type(t_token **tokens);
void		update_state(t_token **token, char ch);
int			is_valid_variable(t_data *data, int i);
int			expand_variables(t_data *data);
int			get_var_key_len(char *str);
int			get_var_len(char *str);//idk about this

#endif
