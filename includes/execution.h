#ifndef EXECUTION_H
#define EXECUTION_H

/* DELETE */
char	*get_path(t_data *data,char *cmd);
int		is_relative_path(char *cmd_name);
int 	create_pipes(t_data *data);
int 	is_builtin(char *cmd);
int 	execute(t_data *data);

#endif
