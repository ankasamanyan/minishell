#include "../include/minishell.h"

void	*input_files(void *infile)
{
	t_pair		*input;
	char		*stringy;
	int			pipy[2];

	input = (t_pair *)infile;
	if (input->second_sign == false)
	{
		if (access(input->filename, F_OK) != 0)
			perror("Minishell\nInput error");
		else if (access(input->filename, R_OK) != 0)
			perror("Minishell\nInput error");
		else
		{
			close(input->cmd->in_fd);
			input->cmd->in_fd = open(input->filename, O_RDONLY);
		}
	}
	if (input->second_sign == true)
	{
		while (42)
		{
			stringy = readline("> ");
			if ((ft_strncmp(stringy, input->filename, ft_strlen(input->filename)) == 0))
				break ;
			else
				write(pipy[WRITE_PIPE], stringy, ft_strlen(stringy)); // ???
			free(stringy);
		}
		free(stringy);
		close(pipy[WRITE_PIPE]);
		close(input->cmd->in_fd);
		input->cmd->in_fd = pipy[READ_PIPE];
	}
	if (input->cmd->out_fd < 0)
		perror("Minishell: Input file error");
}

void	*output_files(void *outfile)
{
	t_pair	*output;

	output = (t_pair *)outfile;
	if (access(output->filename, W_OK) != 0)
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
	if (output->cmd->output->next == NULL)
		output->cmd->out_fd = output->cmd->data->pipe[WRITE_PIPE];
	if (output->cmd->out_fd < 0)
		perror("Minishell: Output file error");
}
