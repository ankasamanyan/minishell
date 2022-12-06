#include "../../include/minishell.h"

/*
Made a case for getcwd failing to give back a path. I honestly have no
idea what could cause such an event, but I don't know what I don't know
so here we are.
*/
bool	pwd(void)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 0);
	if (!path)
		return (msg_error("pwd", E_NOFILDIR, NULL), true);
	printf("%s\n", path);
	free(path);
	return(false);
}
