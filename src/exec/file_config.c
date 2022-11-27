#include "../../include/minishell.h"

void	if_no_input(t_cmd *cmd)
{
	// printf(" . = . %p\n", cmd->data);
	if (cmd->inputlist == NULL)
	{
		if (cmd->data->first)
		{
			close(cmd->fd_in);
			cmd->fd_in = STDIN_FILENO;
			cmd->data->first = false;
		}
		else 
		{
			close(cmd->fd_in);
			cmd->fd_in = cmd->data->pipe[READ_END];
		}
	}
}

void	input_files(void *infile)
{
	t_pair		*input;
	char		*stringy;
	int			pipy[2];

	input = (t_pair *)infile;
	if (input->doublebracket == false)
	{
		if (access(input->string, F_OK) != 0)
			perror("Minishell: Input error");			// if file not existent cmd is not executed but next one is
		else if (access(input->string, R_OK) != 0)
			perror("Minishell: Input error");			// if no permission cmd is not executed but next one is
		else
		{
			close(input->cmd->fd_in);
			input->cmd->fd_in = open(input->string, O_RDONLY);
			if (input->cmd->fd_in < 0)
				perror("Minishell: Input file error");
		}
	}
	if (input->doublebracket == true)
	{
		if(pipe(pipy) != 0)
			perror("Minishell: Pipe() error in heredoc");	//set some flag and exot this function
		while (42)
		{
			stringy = readline("> ");
			if ((ft_strncmp(stringy, input->string, ft_strlen(input->string)) == 0))
				break ;
			else
				write(pipy[WRITE_END], stringy, ft_strlen(stringy)); // ???
			free(stringy);
		}
		free(stringy);
		close(pipy[WRITE_END]);
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
			close(cmd->fd_out);
			cmd->fd_out = STDOUT_FILENO;
		}
		else
		{
			close(cmd->fd_out);
			cmd->fd_out = cmd->data->pipe[WRITE_END];
		}
	}
}

void	output_files(void *outfile)
{
	t_pair	*output;

	// write cmd->next->in_fd = empty pipe
	// pipe(defaultname)
	// cmd->next->in_fd = defaultname[read];
	// close(defaultname[write]);
	output = (t_pair *)outfile;
	if (access(output->string, W_OK) != 0)			// // if file doesnt have write rights cmd is not executed but next one is
		perror("Minishell: Output error");
	else if (output->doublebracket == false)
	{
		close(output->cmd->fd_out);

		output->cmd->fd_out = open(output->string, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	}
	else if (output->doublebracket == true)
	{
		close(output->cmd->fd_out);

		output->cmd->fd_out = open(output->string, O_WRONLY | O_APPEND | O_CREAT, 0777);
	}
	// if (output->cmd->outputlist->next == NULL)
	// 	output->cmd->fd_out = output->cmd->data->pipe[WRITE_END];
	if (output->cmd->fd_out < 0)
		perror("Minishell: Output file error");
}
