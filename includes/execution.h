#ifndef EXECUTION_H
#define EXECUTION_H

/* DELETE */
int		execute_command(t_data *data, t_command *cmd);
int		get_path(t_data *data, t_command *cmd);
int 	handle_descriptors(t_command *cmd);
int		is_relative_path(char *cmd_name);
int 	create_processes(t_data *data);
int 	create_pipes(t_data *data);
int 	is_builtin(char *cmd);
int 	execute(t_data *data);

#endif
