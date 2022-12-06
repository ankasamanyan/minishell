#include "../../include/minishell.h"

/*
Gave echo a return in order for it to have same structure as other builtins.
Might make things easier for exec part.
*/
bool	echo(t_cmd *cmdnode)
{
	int		i;
	bool	flag;

	i = 1;
	flag = false;
	printf("\n");
	if (!ft_strncmp("-f", cmdnode->cmd_arr[1], 3))
	{
		i++;
		flag = true;
	}
	while (cmdnode->cmd_arr[i])
	{
		printf(" %s", cmdnode->cmd_arr[i]);
		i++;
	}
	if (!flag)
		printf("\n");
	return (false);
}
