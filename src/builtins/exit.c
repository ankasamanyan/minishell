#include "../../include/minishell.h"

void	bltn_exit(t_cmd *cmdnode)
{
	int		i;
	int		exitval;

	i = 0;
	exitval = get_exitval(cmdnode->data, cmdnode->cmd_arr);
	del_explist(cmdnode->data->exp_list);
	free2d_char(cmdnode->data->env);
	if (cmdnode->data->parsing_struct.input)
		free(cmdnode->data->parsing_struct.input);
	exit(exitval);
}

int	get_exitval(t_data *data, char **cmds)
{
	int		i;
	int		exitval;

	i = 0;
	exitval = -1;
	if (!cmds[i])
		return (data->exitcode);
	while (cmds[1][i])
	{
		if (!ft_isdigit(cmds[1][i]))
		{
			msg_error("exit", cmds[1], E_NUMARG);
				exitval = 255;
			break ;
		}
	i++;
	}
	if (exitval != 255 && cmds[2])
	{
		msg_error("exit", E_MANYARG, NULL);
		exitval = 1;
	}
}
