#include "../../include/minishell.h"

/*
Gave echo a return in order for it to have same structure as other builtins.
Might make things easier for exec part.
*/
int	echo(t_cmd *cmdnode)
{
	int		i;
	bool	print_newline;

	if (!cmdnode->cmd_arr[1])
	{
		ft_putchar_fd('\n', cmdnode->fd_out);
		return (0);
	}
	i = 1;
	print_newline = true;
	if (!ft_strncmp("-n", cmdnode->cmd_arr[1], 2)
		&& is_onlytargetchar(cmdnode->cmd_arr[1] + 2, 'n'))
	{
		i++;
		print_newline = false;
	}
	while (cmdnode->cmd_arr[i])
	{
		ft_putstr_fd(cmdnode->cmd_arr[i], cmdnode->fd_out);
		if (cmdnode->cmd_arr[i + 1])
			ft_putchar_fd(' ', cmdnode->fd_out);
		i++;
	}
	if (print_newline)
		ft_putchar_fd('\n', cmdnode->fd_out);
	return (false);
}

bool	is_onlytargetchar(char *string, char targetchar)
{
	int		i;

	i = 0;
	while (string[i])
	{
		if (string[i] != targetchar)
			return (false);
		i++;
	}
	return (true);
}

// void	echo_check(t_cmd *cmd)
// {

// }

int	echo_builtin(t_cmd *cmd)
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
	return (0);
}