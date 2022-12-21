/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:35:23 by wmardin           #+#    #+#             */
/*   Updated: 2022/12/21 16:35:24 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	bltn_exit(t_cmd *cmdnode)
{
	shutdown_main(cmdnode->data);
	exit(get_exitval(cmdnode->data, cmdnode->cmd_arr));
}

int	get_exitval(t_data *data, char **cmds)
{
	if (!cmds[1])
		return (data->exitcode);
	if (!is_onlydigits(cmds[1]))
	{
		msg_err("exit", cmds[1], E_NUMARG);
		return (255);
	}
	if (cmds[2])
	{
		msg_err("exit", E_MANYARG, NULL);
		return (1);
	}
	return (ft_atoi(cmds[1]) % 256);
}

bool	is_onlydigits(char *string)
{
	int		i;

	i = 0;
	while (string[i])
	{
		if (!ft_isdigit(string[i]))
			return (false);
		i++;
	}
	return (true);
}
