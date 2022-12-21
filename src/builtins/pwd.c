/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:35:45 by wmardin           #+#    #+#             */
/*   Updated: 2022/12/21 16:35:45 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Made a case for getcwd failing to give back a path. I honestly have no
idea what could cause such an event, but I don't know what I don't know
so here we are.
*/
int	pwd(t_cmd *cmdnode)
{
	char	*path;

	if (cmdnode->cmd_arr[1])
		return (msg_err("pwd", E_MANYARG, NULL), 1);
	path = NULL;
	path = getcwd(path, 0);
	if (!path)
		return (msg_err("pwd", E_NOFILDIR, NULL), 1);
	write(cmdnode->fd_out, path, ft_strlen(path));
	write(cmdnode->fd_out, "\n", 1);
	free(path);
	return (0);
}
