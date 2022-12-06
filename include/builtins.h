#ifndef BUILTINS_H
# define BUILTINS_H

//cd.c
bool	cd(t_cmd *cmdnode);
char	*get_homedir(char **env);
char	*build_absolutepath(char *rel_path);

//pwd.c
bool	pwd(void);

//echo.c
bool	echo(t_cmd *cmdnode);

//env.c
bool	env(t_cmd *cmdnode);

#endif