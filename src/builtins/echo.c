#include "../../include/minishell.h"

/*
Gave echo a return in order for it to have same structure as other builtins.
Might make things easier for exec part.
*/
bool	echo(t_cmd *cmdnode)
{
	(void)cmdnode;
	// int		i;
	// bool	print_newline;

	// i = 1;
	// print_newline = true;
	// // write(1, "\n", 1);
	// if (!ft_strncmp("-f", cmdnode->cmd_arr[1], 3))
	// {
	// 	i++;
	// 	print_newline = false;
	// }
	// while (cmdnode->cmd_arr[i])
	// {
	// 	// printf(" %s", cmdnode->cmd_arr[i]);
	// 	i++;
	// }
	// if (print_newline)
	// 	// write(1, "\n", 1);
	return (false);
}

// void	echo_check(t_cmd *cmd)
// {
	
// }

void	echo_builtin(t_cmd *cmd)
{
	int		i;
	bool	da;

	da = false;
	if (cmd->cmd_arr[0])
	{
		if(cmd->cmd_arr[1])
		{
			int j = 1;
			if (ft_strncmp(cmd->cmd_arr[1], "-n", 2) == 0)
			{
				while (cmd->cmd_arr[1][j])
				{
					if (cmd->cmd_arr[1][j] == 'n')
					{
						i = 2;
						da = true;
					}
					else
					{
						i = 1;
						da = false;
						break;
					}
					j++;
				}
			}
			else
			{
				i = 1;
				da = false;
			}
			while (cmd->cmd_arr[i])
			{
				write(cmd->fd_out, cmd->cmd_arr[i], ft_strlen(cmd->cmd_arr[i]));
				i++;
				if (cmd->cmd_arr[i])
					write(cmd->fd_out, " ", 1);
			}
			if (!da)
				write(cmd->fd_out, "\n", 1);
		}
		else
			write(cmd->fd_out, "\n", 1);
	}
}