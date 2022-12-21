/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasaman <akasaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:24:55 by akasaman          #+#    #+#             */
/*   Updated: 2022/12/21 17:08:22 by akasaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec(void *cmd_list)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmd_list;
	cmd->data->cmd_count++;
	cmd->data->file_err = false;
	if (cmd->cmd_arr && cmd->cmd_arr[0]
		&& ft_strncmp(cmd->cmd_arr[0], "exit", 5) != 0)
		cmd->data->exitcode = 0;
	pipe(cmd->data->pipe);
	if_no_input(cmd);
	ft_lstiter(cmd->inputlist, &input_files);
	if_no_output(cmd);
	ft_lstiter(cmd->outputlist, &output_files);
	if (cmd->data->file_err)
		return ;
	if (cmd->builtin)
		builtins_exec(cmd);
	else
		pipex(cmd);
	close_them_all(cmd);
}

void	kiddi_process(t_cmd *cmd)
{
	signal(SIGINT, SIG_DFL);
	if (cmd->data->file_err)
		exit (0);
	if (cmd->fd_in > 2)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out > 2)
		dup2(cmd->fd_out, STDOUT_FILENO);
	execve(cmd->data->full_path, cmd->cmd_arr, cmd->data->env);
	perror("Minishell: Execve error");
	exit(-1);
}

void	pipex(t_cmd *cmd)
{
	search_path_env(cmd);
	find_cmd_path(cmd);
	if (cmd->cmd_arr)
	{
		if (!cmd->data->halp)
			return ;
		if (ft_strncmp((cmd->cmd_arr[0])
				+ (ft_strlen(cmd->cmd_arr[0]) - 9), "minishell", 10) == 0)
			setup_parent_signals();
		else
			exec_parent();
		cmd->data->pid = fork();
		if (cmd->data->pid == 0 && cmd->builtin == false)
			kiddi_process(cmd);
		else
		{
			waitpid(cmd->data->pid, &cmd->data->exitcode, 0);
			if (cmd->data->exitcode != 0)
				cmd->data->exitcode += 128;
			smth_cedric_needs();
			if (cmd->data->full_path)
				free(cmd->data->full_path);
			cmd->data->full_path = NULL;
		}
	}
}

void	close_them_all(t_cmd *cmd)
{
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	if (cmd->data->pipe[WRITE_END] > 2)
		close(cmd->data->pipe[WRITE_END]);
	if (cmd->data->temp_pipe > 2)
		close(cmd->data->temp_pipe);
	cmd->data->temp_pipe = cmd->data->pipe[READ_END];
	if (cmd->data->cmd_count == ft_lstsize(cmd->data->cmd_list) + 1)
		close(cmd->data->temp_pipe);
}
