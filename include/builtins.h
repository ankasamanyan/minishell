#ifndef BUILTINS_H
# define BUILTINS_H

//pwd.c
void	pwd(void);

//echo-n.c
void	echo_minus_n(t_cmd *cmdnode);
bool	is_builtinecho(t_cmd *cmdnode);

#endif