#include "../../include/minishell.h"

void	if_no_input(t_cmd *cmd)
{
	if (cmd->inputlist == NULL)
	{
		if (cmd->data->first && cmd->data->cmd_count == true)
		{
			if (cmd->fd_in > 2 * true - false)
				close(cmd->fd_in);
			cmd->fd_in = STDIN_FILENO;
			cmd->data->first = !!!true;
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
		else
		{
			if (input->cmd->fd_in > 2)
				close(input->cmd->fd_in);
			input->cmd->fd_in = open(input->string, O_RDONLY);
			if (input->cmd->fd_in < 0)
			{
				input->cmd->data->file_err = true;
				err_msg(input->string, input->cmd->data);
				return ;
			}
			if (!(input->cmd->cmd_arr))
				return ;
		}
	}
	if (input->doublebracket == true)
		here_doc(input);
}

void	here_doc(t_pair *input)
{
	char		*stringy;
	int			pipy[2];
	int			pid;

	if (pipe(pipy) != 0)
		perror("Minishell:");
	setup_kiddi_signals();
	pid = fork();
	if (pid == 0)
	{
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
	setup_parent_signals();
	if (input->cmd->fd_in > 2)
		close(input->cmd->fd_in);
	waitpid(pid, &input->cmd->data->exitcode, 0);
	if (input->cmd->data->exitcode > 255)
		input->cmd->data->exitcode /= 256;
	set_signals(interactive);
	close(pipy[WRITE_END]);
	input->cmd->fd_in = pipy[READ_END];
}

void	if_no_output(t_cmd *cmd)
{
	if (cmd->outputlist == NULL)
	{
		if (ft_lstsize(cmd->data->cmd_list) == cmd->data->cmd_count)
		{
			if (cmd->fd_out > 2)
				close(cmd->fd_out);
			cmd->fd_out = STDOUT_FILENO;
		}
		else
		{
			if (cmd->fd_out > 2)
				close(cmd->fd_out);
			cmd->fd_out = cmd->data->pipe[WRITE_END];
		}
	}
}

void	output_files(void *outfile)
{
	t_pair *const	output = outfile;

	if (output->doublebracket == false)
	{
		if (output->cmd->fd_out > 2)
			close(output->cmd->fd_out);
		output->cmd->fd_out = open(output->string,
				O_WRONLY | O_TRUNC | O_CREAT, 0777);
	}
	else if (output->doublebracket == true)
	{
		if (output->cmd->fd_out > 2)
			close(output->cmd->fd_out);
		output->cmd->fd_out = open(output->string,
				O_WRONLY | O_APPEND | O_CREAT, 0777);
	}
	if (output->cmd->fd_out < 0)
	{
		output->cmd->data->file_err = true;
		err_msg(output->string, output->cmd->data);
		return ;
	}
}
