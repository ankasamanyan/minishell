#include "../include/minishell.h"

void	if_no_input(t_cmd *cmd)
{
	if (cmd->input->content == NULL)
	{
		if (cmd->data->first)
		{
			close(cmd->in_fd);
			cmd->in_fd = STDIN_FILENO;
			cmd->data->first = false;
		}
		else 
		{
			close(cmd->in_fd);
			cmd->in_fd = cmd->data->pipe[READ_END];
		}
	}
}

void	input_files(void *infile)
{
	t_pair		*input;
	char		*stringy;
	int			pipy[2];

	input = (t_pair *)infile;
	if (input->second_sign == false)
	{
		if (access(input->filename, F_OK) != 0)
			perror("Minishell\nInput error");			// if file not existent cmd is not executed but next one is
		else if (access(input->filename, R_OK) != 0)
			perror("Minishell\nInput error");			// if no permission cmd is not executed but next one is
		else
		{
			close(input->cmd->in_fd);
			input->cmd->in_fd = open(input->filename, O_RDONLY);
			if (input->cmd->in_fd < 0)
				perror("Minishell: Input file error");
		}
	}
	if (input->second_sign == true)
	{
		if(pipe(pipy) != 0)
			perror("Minishell: Pipe() error in heredoc");	//set some flag and exot this function
		while (42)
		{
			stringy = readline("> ");
			if ((ft_strncmp(stringy, input->filename, ft_strlen(input->filename)) == 0))
				break ;
			else
				write(pipy[WRITE_END], stringy, ft_strlen(stringy)); // ???
			free(stringy);
		}
		free(stringy);
		close(pipy[WRITE_END]);
		close(input->cmd->in_fd);
		input->cmd->in_fd = pipy[READ_END];
	}
}

void	if_no_output(t_cmd *cmd)
{
	if (cmd->output->content == NULL)
	{
		if (ft_lstsize(cmd->data->cmd_list) == cmd->data->cmd_count)
		{
			close(cmd->out_fd);
			cmd->out_fd = STDOUT_FILENO;
		}
		else
		{
			close(cmd->out_fd);
			cmd->out_fd = cmd->data->pipe[WRITE_END];
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
	if (access(output->filename, W_OK) != 0)			// // if file doesnt have write rights cmd is not executed but next one is
		perror("Minishell: Output error");
	else if (output->second_sign == false)
	{
		close(output->cmd->out_fd);

		output->cmd->out_fd = open(output->filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	}
	else if (output->second_sign == true)
	{
		close(output->cmd->out_fd);

		output->cmd->out_fd = open(output->filename, O_WRONLY | O_APPEND | O_CREAT, 0777);
	}
	// if (output->cmd->output->next == NULL)
	// 	output->cmd->out_fd = output->cmd->data->pipe[WRITE_END];
	if (output->cmd->out_fd < 0)
		perror("Minishell: Output file error");
}
