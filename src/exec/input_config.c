/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasaman <akasaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:24:53 by akasaman          #+#    #+#             */
/*   Updated: 2022/12/21 16:24:54 by akasaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	if_no_input(t_cmd *cmd)
{
	if (cmd->inputlist == NULL)
	{
		if (cmd->data->first && cmd->data->cmd_count == true)
		{
			if (cmd->fd_in > 2)
				close(cmd->fd_in);
			cmd->fd_in = STDIN_FILENO;
			cmd->data->first = false;
		}
		else
		{
			if (cmd->fd_in > 2)
				close(cmd->fd_in);
			cmd->fd_in = cmd->data->temp_pipe;
		}
	}
}

void	input_files(void *infile)
{
	t_pair *const	input = infile;

	if (input->cmd->data->temp_pipe > 2)
		close(input->cmd->data->temp_pipe);
	if (input->doublebracket == false)
	{
		if (access(input->string, F_OK) != 0)
		{
			input->cmd->data->file_err = true;
			err_msg(input->string, input->cmd->data);
			return ;
		}
		else if (access(input->string, R_OK) != 0)
		{
			input->cmd->data->file_err = true;
			err_msg(input->string, input->cmd->data);
			return ;
		}
		else if (configsss(input))
			return ;
	}
	if (input->doublebracket == true)
		here_doc(input);
}

int	configsss(t_pair *input)
{
	if (input->cmd->fd_in > 2)
		close(input->cmd->fd_in);
	input->cmd->fd_in = open(input->string, O_RDONLY);
	if (input->cmd->fd_in < 0)
	{
		input->cmd->data->file_err = true;
		err_msg(input->string, input->cmd->data);
		return (1);
	}
	if (!(input->cmd->cmd_arr))
		return (1);
	return (0);
}

void	here_doc_kiddy(t_pair *input, int *pipy)
{
	char		*stringy;

	while (42)
	{
		stringy = readline("> ");
		if (!stringy)
			exit(0);
		stringy = append_char(stringy, '\n');
		if ((ft_strncmp(stringy, input->string,
					ft_strlen(input->string)) == 0)
			&& (stringy[ft_strlen(input->string) + 1] == '\0')
			&& (stringy[ft_strlen(input->string)] == '\n') && stringy)
			break ;
		else
			write(pipy[WRITE_END], stringy, ft_strlen(stringy));
		free(stringy);
	}
	free(stringy);
	close(pipy[WRITE_END]);
	close(pipy[READ_END]);
	exit(0);
}

void	here_doc(t_pair *input)
{
	int			pipy[2];
	int			pid;

	if (input->cmd->fd_in > 2)
		close(input->cmd->fd_in);
	if (pipe(pipy) != 0)
		perror("Minishell:");
	setup_kiddi_signals();
	pid = fork();
	if (pid == 0)
		here_doc_kiddy(input, pipy);
	setup_parent_signals();
	waitpid(pid, &input->cmd->data->exitcode, 0);
	if (input->cmd->data->exitcode > 255)
		input->cmd->data->exitcode /= 256;
	set_signals(interactive);
	close(pipy[WRITE_END]);
	input->cmd->fd_in = pipy[READ_END];
}
