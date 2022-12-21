/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasaman <akasaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:24:50 by akasaman          #+#    #+#             */
/*   Updated: 2022/12/21 17:45:11 by akasaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	path_access(t_cmd *cmd, char **smoll_pathsies)
{
	char	*lil_path;
	int		i;

	i = 0;
	if (smoll_pathsies)
	{
		while (smoll_pathsies[i])
		{
			lil_path = ft_triple_strjoin(smoll_pathsies[i++],
					"/", cmd->cmd_arr[0]);
			if (access(lil_path, X_OK) == 0)
			{
				cmd->data->full_path = lil_path;
				cmd->data->halp = true;
				return ;
			}
			else
				free(lil_path);
		}
	}
}

void	find_cmd_path(t_cmd *cmd)
{
	char	**smoll_pathsies;
	int		aaaaa;

	aaaaa = 1;
	cmd->data->halp = false;
	if (cmd->cmd_arr && cmd->cmd_arr[0])
	{
		if (ft_strlen(cmd->cmd_arr[0]) == 0)
			return (err_cmd_not_found(cmd->cmd_arr[0], aaaaa, cmd->data));
		smoll_pathsies = ft_split(cmd->data->big_path, ':');
		cmd->data->full_path = NULL;
		path_access(cmd, smoll_pathsies);
		if (access(cmd->cmd_arr[0], X_OK) == 0)
		{
			cmd->data->full_path = ft_strdup(cmd->cmd_arr[0]);
			cmd->data->halp = true;
		}
		else
			if (access(cmd->cmd_arr[0], F_OK) == 0)
				aaaaa = 2;
		ft_free_array(smoll_pathsies);
		if (!cmd->data->halp)
			err_cmd_not_found(cmd->cmd_arr[0], aaaaa, cmd->data);
	}
}

void	search_path_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->data->big_path)
	{
		free(cmd->data->big_path);
		cmd->data->big_path = NULL;
	}
	if (cmd->data->env)
	{
		while (cmd->data->env[i])
		{
			if (ft_strncmp(cmd->data->env[i], "PATH=", 5) == 0)
			{
				cmd->data->big_path = ft_strdup(cmd->data->env[i] + 5);
				break ;
			}
			i++;
		}
	}
	if (!cmd->data->env)
		cmd->data->big_path = ft_strdup("");
}
