#include "../../include/minishell.h"

void	bltn_exit(t_cmd *cmdnode)
{
	int		exitval;

	if (cmdnode->cmd_arr[1])
		exitval = get_exitval(cmdnode->data, cmdnode->cmd_arr);
	shutdown_main(cmdnode->data);
	exit(exitval);
}

int	get_exitval(t_data *data, char **cmds)
{
	int		exitval;

	exitval = -1;
	if (!cmds[1])
		return (data->exitcode);
	if (!is_onlydigits(cmds[1]))
	{
		msg_error("exit", cmds[1], E_NUMARG);
		exitval = 255;
	}
	if (exitval != 255 && cmds[2])
	{
		msg_error("exit", E_MANYARG, NULL);
		exitval = 1;
	}
	return (exitval);
}

bool	is_onlydigits(char *string)
{
	int		i;

	i = 0;
	while (string[i])
	{
		if (!ft_isdigit(string[i]))
			return (false);
		i++;
	}
	return (true);
}
