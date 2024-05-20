#ifndef EXPANSION_H
#define EXPANSION_H

/* EXPANSION */
int			replace_old_content(t_token **tokens, char *var_value, int index);
int 		erase_variable(t_token **token, char *content, int index);
int			update_content(t_data *data, char *var_value, int i);
char		*get_variable_value(t_data *data, char *str);
void		update_state(t_token **token, char ch);
void 		update_env_token_type(t_token **tokens);
int			is_valid_variable(t_data *data, int i);
int			expand_variables(t_data *data);
int			get_var_key_len(char *str);
int 		get_var_len(char *str);

#endif