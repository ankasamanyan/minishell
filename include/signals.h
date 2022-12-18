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
/* normal parents */
void	smth_cedric_needs(void);
/* here_doc signals */
void	kiddi_signals(int signal);
void	setup_kiddi_signals(void);
void	setup_parent_signals(void);
/*  */
void	signal_thingy(int smth);
void	exec_parent(void);


#endif