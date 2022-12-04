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

/*
Function used during exec part to test if echo should be
execve'd or builtin'd.

Prolly take out the direct call of echo_minus_n from return.
Left it here for testing purposes.

For echo it should be like this
if (!ft_strncmp("echo", cmdnode->cmd_arr[0], 5)
		&& cmdnode->cmd_arr[1] && !ft_strncmp("-n", cmdnode->cmd_arr[1], 3))
	call our function
else
	execve echo with whatever flag
*/
bool	is_builtinecho(t_cmd *cmdnode)
{
	if (!ft_strncmp("echo", cmdnode->cmd_arr[0], 5)
		&& cmdnode->cmd_arr[1]
		&& !ft_strncmp("-n", cmdnode->cmd_arr[1], 3))
		return (echo_minus_n(cmdnode), true);
	return (false);
}
