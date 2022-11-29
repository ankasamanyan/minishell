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
	return (true);
}

/*
check for bash exit codes depending on exit case
*/
// void	onexit(t_data *data)
// {
// 	int		j;

// 	j = 0;
// 	while (data->env[j])
// 	{
// 		// if (ft_strncmp(data->env[j], "SHLVL=", 6) == 0)
// 			// free(data->env[j]);
// 		j++;
// 	}
// 	exit(0);
// }
void	commandexit(void)
{

	write(1, "exit\n", 6);
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
