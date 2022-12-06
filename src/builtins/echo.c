#include "../../include/minishell.h"

/*
Gave echo a return in order for it to have same structure as other builtins.
Might make things easier for exec part.
*/
bool	echo(t_cmd *cmdnode)
{
	int		i;
	bool	print_newline;

	i = 1;
	print_newline = true;
	write(1, "\n", 1);
	if (!ft_strncmp("-f", cmdnode->cmd_arr[1], 3))
	{
		i++;
		print_newline = false;
	}
	while (cmdnode->cmd_arr[i])
	{
		printf(" %s", cmdnode->cmd_arr[i]);
		i++;
	}
	if (print_newline)
		write(1, "\n", 1);
	return (false);
}
