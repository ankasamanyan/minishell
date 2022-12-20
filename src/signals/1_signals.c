#include "../../include/minishell.h"

/*
Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
• In interactive mode:
	ctrl-C displays a new prompt on a new line.
	ctrl-D exits the shell.
	ctrl-\ does nothing.

ctrl-c	-> SIGINT
ctrl-\	-> SIGQUIT
ctr-d	-> is not a signal. Represents EOF.
*/

/*
Initializes sigaction struct new_action:
-	Sets the member sa_handler (makro) to the desired function or
	makro (SIG_IGN or SIG_DFL).
-	Inits mask to empty by calling sigemptyset
-	Inits flags to 0
-	Sets restorer to NULL (didn't read up on this one tbh)
Sets newaction to handle SIGINT.
Calls sigaction to set behavior for each signal to the actions
specified in new_action.
*/
/* void	signals_sigaction(void)
{
	struct sigaction	new_action;

	new_action.sa_handler = sig_handler;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;
	//new_action.sa_restorer = NULL;
	sigaction(SIGINT, &new_action, NULL);
	new_action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &new_action, NULL);
} */

void	set_signals(t_sigtype sig_type)
{
	if (sig_type == interactive)
	{
		signal(SIGINT, sig_newline);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig_type == child)
	{

	}
	if (sig_type == child)
	{

	}
	if (sig_type == ignore)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	signals_interactive(void)
{
	signal(SIGINT, sig_newline);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_exitoninterrupt(void)
{
	// if ctrl c set exitcd to 130
}

/*
Usually, this function would handle more signals. But we only have to handle
SIGINT so the if clause isn't necessary. Kept it because the structure is
correct this way and doesn't have to void sig.
-	replaces current line with empty string so redisplay doesn't
	keep the current contents of readline.
-	Starts a new line
-	need to put \n to make the prompt reappear on the next line
-	redisplay makes the prompt reappear
*/
void	sig_newline(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write (1, "\n", 1);
		rl_redisplay();
	}
}



void	smth_cedric_needs(void)
{
	signal(SIGINT, sig_newline);
	signal(SIGQUIT, SIG_IGN); // der Vater (getting milk right now)//at least he is not ignoring the milk
}


void	kiddi_signals(int signal)
{
	(void)signal;
	exit(1);
}

void	setup_kiddi_signals(void)
{
	signal(SIGINT, kiddi_signals);
	signal(SIGQUIT, SIG_IGN);
}

// void	cedyy(int signal)
// {
// 	(void)signal;
// 	data.exitcode = 130;
// }

	// signal(SIGINT, cedyy);
	// signal(SIGQUIT, cedyy);
void	setup_parent_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}


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







