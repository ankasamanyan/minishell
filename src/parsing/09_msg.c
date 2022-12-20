#include "../../include/minishell.h"

void	msg_senut(char c, bool unclosed_quote)
{
	if (c == '\n')
	{
		ft_putstr_fd(E_SENUT, 2);
		ft_putstr_fd("newline'", 2);
	}
	else
	{
		ft_putstr_fd(E_SENUT, 2);
		write(2, &c, 1);
		write(2, "'", 1);
	}
	if (unclosed_quote)
		ft_putstr_fd(E_UNCLOSEDQUOTE, 2);
	ft_putstr_fd("\n", 2);
}

/*
Format:
printf("minishell: %s: %s: %s", err_msg0, err_msg1, err_msg2)
Send NULL if string 2 or 3 not needed, will skip accordingly.
*/
void	msg_err(char *err_msg0, char *err_msg1, char *err_msg2)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(err_msg0, 2);
	if (err_msg1)
	{
		write(2, ": ", 2);
		ft_putstr_fd(err_msg1, 2);
	}
	if (err_msg2)
	{
		write(2, ": ", 2);
		ft_putstr_fd(err_msg2, 2);
	}
	write (2, "\n", 1);
}

/*
Format:
printf("minishell: %s: `%s': %s", err_msg0, err_msg1, err_msg2)
Send NULL if string 2 or 3 not needed, will skip accordingly.
But the point of this function is that string 2 will be quoted.
*/
void	msg_err_wquote(char *err_msg0, char *err_msg1, char *err_msg2)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(err_msg0, 2);
	if (err_msg1)
	{
		write(2, ": `", 3);
		ft_putstr_fd(err_msg1, 2);
		write(2, "\'", 1);
	}
	if (err_msg2)
	{
		write(2, ": ", 2);
		ft_putstr_fd(err_msg2, 2);
	}
	write (2, "\n", 1);
}
