/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasaman <akasaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:24:47 by akasaman          #+#    #+#             */
/*   Updated: 2022/12/21 16:24:48 by akasaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtins_exec(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd_arr[0], "export", ft_strlen("export")) == 0)
		cmd->data->exitcode = export(cmd);
	else if (ft_strncmp(cmd->cmd_arr[0], "env", ft_strlen("env")) == 0)
		cmd->data->exitcode = env(cmd);
	else if (ft_strncmp(cmd->cmd_arr[0], "pwd", ft_strlen("pwd")) == 0)
		cmd->data->exitcode = pwd(cmd);
	else if (ft_strncmp(cmd->cmd_arr[0], "cd", ft_strlen("cd")) == 0)
		cmd->data->exitcode = cd(cmd);
	else if (ft_strncmp(cmd->cmd_arr[0], "echo", ft_strlen("echo")) == 0)
		cmd->data->exitcode = echo(cmd);
	else if (ft_strncmp(cmd->cmd_arr[0], "unset", ft_strlen("unset")) == 0)
		cmd->data->exitcode = unset(cmd);
	else if (ft_strncmp(cmd->cmd_arr[0], "exit", ft_strlen("exit")) == 0
		&& ft_lstsize(cmd->data->cmd_list) == 1)
		bltn_exit(cmd);
}
