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

void	echo_builtin(t_cmd *cmd)
{
	int		i;

	// write(cmd->fd_out, "AAAAAAAAAAAAAAAAA\n", 1);
	// write(1, ft_itoa(cmd->fd_out), ft_strlen(ft_itoa(cmd->fd_out)));
	// print_2d_array(cmd->cmd_arr, 2);
	// printf("stop of 2d array\n");
	// printf("");
	if (cmd->cmd_arr[0])
	{
		if(cmd->cmd_arr[1])
		{
			if (ft_strncmp(cmd->cmd_arr[1], "-n", 3) == 0)
				i = 2;
			else
				i = 1;
			while (cmd->cmd_arr[i])
			{
				write(cmd->fd_out, cmd->cmd_arr[i], ft_strlen(cmd->cmd_arr[i]));
				i++;
				if (cmd->cmd_arr[i])
					write(cmd->fd_out, " ", 1);
			}
			if (ft_strncmp(cmd->cmd_arr[1], "-n", 3) != 0)
				write(cmd->fd_out, "\n", 1);
		}
		else
			write(cmd->fd_out, "\n", 1);
	}
}