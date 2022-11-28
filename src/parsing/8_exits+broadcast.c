#include "../../include/minishell.h"

void	errorexit_onlymsg(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

bool	broadcast_senut(char c)
{
	if (c == '\n')
		printf("%s `newline'\n", E_SENUT);
	else
		printf("%s `%c'\n", E_SENUT, c);
	exit(EXIT_FAILURE);
	return (true);
}

/*
check for bash exit codes depending on exit case
*/
void	commandexit(void)
{
	write(1, "exit\n", 5);
	exit(2);
}
/*
void	error_msg_exit(STRUCT knudel, char *msg)
{
	perror(msg);
	shutdown(knudel);
	exit(EXIT_FAILURE);
}
*/
