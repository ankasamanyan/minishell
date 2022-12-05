#include "../../include/minishell.h"

void	echo_minus_n(t_cmd *cmdnode)
{
	int		i;

	i = 2;
	printf("\n");
	while (cmdnode->cmd_arr[i])
	{
		printf(" %s", cmdnode->cmd_arr[i]);
		i++;
	}
}
