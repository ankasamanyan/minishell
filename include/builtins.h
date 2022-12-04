#ifndef BUILTINS_H
# define BUILTINS_H

//cd.c
void	cd(t_data *data, char *inputpath);
char	*get_homedir(char **env);

//pwd.c
void	pwd(void);

//echo-n.c
void	echo_minus_n(t_cmd *cmdnode);
bool	is_builtinecho(t_cmd *cmdnode);

//env.c
void	env(t_data *data);

#endif