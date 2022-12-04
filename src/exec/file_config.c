#include "../../include/minishell.h"

void	if_no_input(t_cmd *cmd)
{
	// printf(" . = . %p\n", cmd->data);
	if (cmd->inputlist == NULL)
	{
		if (cmd->data->first && cmd->data->cmd_count == 1)
		{
			// printf("HELLO\n");
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
	t_pair		*input;
	char		*stringy;
	int			pipy[2];

	input = (t_pair *)infile;
	if (input->cmd->data->temp_pipe > 2)
		close(input->cmd->data->temp_pipe);
	if (input->doublebracket == false)
	{
		if (access(input->string, F_OK) != 0)
			perror("Minishell: Input error");			// if file not existent cmd is not executed but next one is
		else if (access(input->string, R_OK) != 0)
			perror("Minishell: Input error");			// if no permission cmd is not executed but next one is
		else
		{
			if (input->cmd->fd_in > 2)
				close(input->cmd->fd_in);
			input->cmd->fd_in = open(input->string, O_RDONLY);
			if (input->cmd->fd_in < 0)
				perror("Minishell: Input file error");
			if (!(input->cmd->cmd_arr))
			{
				//you don't have to close alllllll the fdsss
				//leave ze pipe!!!!!!!!!!!
				return ;
			}
			// helper function that finds out if there is no cmd 
			// and closeall the pipes	
		}
	}
	if (input->doublebracket == true)
	{
		if(pipe(pipy) != 0)
			perror("Minishell: Pipe() error in heredoc");	//set some flag and exot this function
		while (42)
		{
			stringy = readline("> ");
			stringy = append_char(stringy, '\n');
			if ((ft_strncmp(stringy, input->string, ft_strlen(input->string)) == 0)
				&& (stringy[ft_strlen(input->string) + 1] == '\0') && (stringy[ft_strlen(input->string)] == '\n'))
				break ;
			else
				write(pipy[WRITE_END], stringy, ft_strlen(stringy)); // ???
			free(stringy);
		}
		free(stringy);
		close(pipy[WRITE_END]);
		if (input->cmd->fd_in > 2)
			close(input->cmd->fd_in);
		input->cmd->fd_in = pipy[READ_END];
	}
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
	t_pair	*output;

	output = (t_pair *)outfile;
	if (output->doublebracket == false)
	{
		if (output->cmd->fd_out > 2)
			close(output->cmd->fd_out);
		output->cmd->fd_out = open(output->string, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (output->cmd->fd_out < 0)
			perror("Minishell: Output file error");
	}
	else if (output->doublebracket == true)
	{
		if (output->cmd->fd_out > 2)
			close(output->cmd->fd_out);
		output->cmd->fd_out = open(output->string, O_WRONLY | O_APPEND | O_CREAT, 0777);
	}
}
