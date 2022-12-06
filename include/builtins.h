#ifndef BUILTINS_H
# define BUILTINS_H

//cd.c
bool	cd(t_cmd *cmdnode);
char	*get_homedir(char **env);
char	*build_absolutepath(char *rel_path);

//pwd.c
void	pwd(void);

//echo-n.c
void	echo_minus_n(t_cmd *cmdnode);
bool	is_builtinecho(t_cmd *cmdnode);

//env.c
void	env(t_data *data);

#endif