#include "../../include/minishell.h"

/*
Made a case for getcwd failing to give back a path. I honestly have no
idea what could cause such an event, but I don't know what I don't know
so here we are.
*/
int	pwd(t_cmd *cmdnode)
{
	char	*path;

	if (cmdnode->cmd_arr[1])
		return (msg_err("pwd", E_MANYARG, NULL), true);
	path = NULL;
	path = getcwd(path, 0);
	if (!path)
		return (msg_err("pwd", E_NOFILDIR, NULL), true);
	write(cmdnode->fd_out, path, ft_strlen(path));
	write(cmdnode->fd_out, "\n", 1);
	free(path);
	return (false);
}
