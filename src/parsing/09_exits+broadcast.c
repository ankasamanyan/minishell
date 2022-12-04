#include "../../include/minishell.h"

void	errorexit_onlymsg(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	msg_senut(char c)
{
	if (c == '\n')
	{
		ft_putstr_fd(E_SENUT, 2);
		ft_putstr_fd("newline'\n", 2);
	}
	else
	{
		ft_putstr_fd(E_SENUT, 2);
		write(2, &c, 1);
		ft_putstr_fd("'\n", 2);
	}
}

void	msg_bltnwithflag(char *string)
{
	ft_putstr_fd(E_BLTNFLAG, 2);
	ft_putstr_fd(string, 2);
	ft_putstr_fd("'\n", 2);
}

void	msg_bltnfail(char *cmd_name, char *err_msg1, char *err_msg2)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	if (err_msg1)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(err_msg1, 2);
	}
	if (err_msg2)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(err_msg2, 2);
	}
	write (2, "\n", 1);
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
