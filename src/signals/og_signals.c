#include "../../include/minishell.h"

// exec child
void	signal_thingy(int smth)
{
	if (smth == SIGINT)
		ft_putchar_fd('\n', STDERR_FILENO);
	else if (smth == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
}

// exec parent
void	exec_parent(void)
{
	signal(SIGINT, signal_thingy);
	signal(SIGQUIT, signal_thingy);
}

void	smth_cedric_needs(void)
{
	signal(SIGINT, sig_newline);
	signal(SIGQUIT, SIG_IGN);
}

void	kiddi_signals(int signal)
{
	(void)signal;
}

void	setup_kiddi_signals(void)
{
	signal(SIGINT, kiddi_signals);
	signal(SIGQUIT, SIG_IGN);
}
