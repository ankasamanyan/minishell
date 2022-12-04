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
void	signals(void)
{
	struct sigaction	new_action;

	new_action.sa_handler = sig_handler;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;
	// new_action.sa_restorer = NULL;
	sigaction(SIGINT, &new_action, NULL);
	new_action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &new_action, NULL);
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
void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		// rl_replace_line("", 0);
		rl_on_new_line();
		write (1, "\n", 1);
		rl_redisplay();
	}
}
