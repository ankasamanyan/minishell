#ifndef SIGNALS_H
# define SIGNALS_H

typedef enum sig_type
{
	interactive = 1,
	child = 2,
	heredoc = 4,
	ignore = 8
}	t_sigtype;

//1_signals.c
void	set_signals(t_sigtype sig_type);
void	sig_newline(int sig);

#endif