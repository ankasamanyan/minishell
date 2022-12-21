/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_check_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:05:45 by wmardin           #+#    #+#             */
/*   Updated: 2022/12/20 21:39:20 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Checks for presence of a builtin and sets the builtin bool
accordingly.
*/
void	check_builtin(t_par *p)
{
	t_list		*temp;
	t_cmd		*cmdnode;

	cmdnode = p->cmdlist->content;
	temp = p->cmdlist;
	while (temp)
	{
		cmdnode = temp->content;
		cmdnode->builtin = is_builtin(cmdnode);
		temp = temp->next;
	}
}

bool	is_builtin(t_cmd *cmdnode)
{
	if (!cmdnode->cmd_arr || !cmdnode->cmd_arr[0])
		return (false);
	if (!ft_strncmp("pwd", cmdnode->cmd_arr[0], 4)
		|| !ft_strncmp("export", cmdnode->cmd_arr[0], 7)
		|| !ft_strncmp("unset", cmdnode->cmd_arr[0], 6)
		|| !ft_strncmp("env", cmdnode->cmd_arr[0], 4)
		|| !ft_strncmp("exit", cmdnode->cmd_arr[0], 5)
		|| !ft_strncmp("echo", cmdnode->cmd_arr[0], 5)
		|| !ft_strncmp("cd", cmdnode->cmd_arr[0], 3))
		return (true);
	return (false);
}
