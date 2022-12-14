/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:35:20 by wmardin           #+#    #+#             */
/*   Updated: 2022/12/21 16:35:20 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env(t_cmd *cmdnode)
{
	t_data	*data;
	int		i;

	if (cmdnode->cmd_arr[1])
		return (msg_err("env", E_MANYARG, NULL), 1);
	data = cmdnode->data;
	if (!data->env)
		return (msg_err("env", "not found", NULL), 1);
	i = 0;
	while (data->env[i])
	{
		write(cmdnode->fd_out, data->env[i], ft_strlen(data->env[i]));
		write(cmdnode->fd_out, "\n", 1);
		i++;
	}
	return (0);
}

/*
env is the list of export variables that are declared and defined.
E.g. "export i=0" will result in i being added to env.
"export i" will not result in i being added to env (only to export).
This function (re)builds env from the export list.
It is called at the start of minishell to create the starting env version.
It is also called whenever export makes a modification to the export list.
*/
void	build_env(t_data *data, t_list *exp_list)
{
	t_list		*temp;
	char		*string;
	t_exp		*expnode;

	if (data->env)
		free2d_char(data->env);
	data->env = NULL;
	temp = exp_list;
	while (temp)
	{
		expnode = temp->content;
		if (expnode->value)
		{
			string = ft_strjoin(expnode->name, "=");
			data->env = append_string(data->env,
					ft_strjoin(string, expnode->value));
			free (string);
		}
		temp = temp->next;
	}
}
