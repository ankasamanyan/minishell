/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasaman <akasaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:39:13 by akasaman          #+#    #+#             */
/*   Updated: 2022/12/21 16:39:14 by akasaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

typedef enum sig_mode
{
	interactive = 1,
	child = 2,
	heredoc = 4,
	ignore = 8
}	t_sigmode;

//signals.c
void	set_signals(t_sigmode sig_type);
void	sig_newline(int sig);
/* normal parents */
void	smth_cedric_needs(void);
/* here_doc signals */
void	kiddi_signals(int signal);
void	setup_kiddi_signals(void);
void	setup_parent_signals(void);
/* Welllll */
void	signal_thingy(int smth);
void	exec_parent(void);

#endif