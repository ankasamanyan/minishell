#include "../include/minishell.h"

void	find_lil_path(char *big_path, t_data *data)
{
	char	**smoll_pathsies;
	char	*lil_path;
	t_cmd	*cmd_w_flags;
	int		i;

	i = 0;
	cmd_w_flags = (t_cmd *)data->cmd_list->content;
	smoll_pathsies = ft_split(big_path, ':');
	data->exec->full_path = NULL;
	while (smoll_pathsies[i])
	{
		lil_path = ft_triple_strjoin(smoll_pathsies[i++],
				"/", cmd_w_flags->cmd_arr[0]);
		if (access(lil_path, X_OK) == 0)
			data->exec->full_path = lil_path;
		else
		{
			access(lil_path, F_OK);
			free(lil_path);
		}
	}
	if (access(cmd_w_flags->cmd_arr[0], X_OK) == 0)
		data->exec->full_path = ft_strdup(cmd_w_flags->cmd_arr[0]);
	else
		access(cmd_w_flags->cmd_arr[0], F_OK);
	ft_free_array(smoll_pathsies);
}

void	*input_files(void *infile)
{
	t_pair		*input;
	char		*stringy;
	int			pipy[2];

	input = (t_pair *)infile;
	if (input->second_sign == false)
	{
		if (access(input->filename, F_OK) != 0)
			perror("Minishell😿:");
		else if (access(input->filename, R_OK) != 0)
			perror("Minishell😿:");
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
		perror("Minishell😿: Input file error");
}

void	*output_files(void *outfile)
{
	t_pair	*output;

	output = (t_pair *)outfile;
	if (access(output->filename, W_OK) != 0)
		perror("Minishell😿:");
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
		perror("Minishell😿: Output file error");
}

void	*exec(void *cmd_list)
{
	int		pid;
	t_cmd	*cmd;

	cmd = (t_cmd *)cmd_list;
	pipe(cmd->data->pipe);
	ft_lstiter(cmd->input, &input_files); //input checks
	ft_lstiter(cmd->output, &output_files); //output checks


	pid = fork();
	if (pid == 0)
		//kiddi_process();
	else
	{
		// wait for kiddi
		// set temp_pipe													close pipe[read]
		// close pipe[write]	
	}


}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;

	int		pid;
	t_data	data;
	t_exec	*exec;

	
	ft_lstiter(t_list *cmd, &exec);


	//fork
	// find the path to the conmmand 
	// execute the command 
	// dup to pipe 
	// find next command 
	// execute the next command 
	return 0;
}

// void	execute_comand_for_real()
// {
// 	// dup
// 	// close (temp_pipe[read])
// 	// execve
// }

// void	exec_cmd(void *cmd_list)
// {
// 	t_cmd	*cmd;

// 	// cmd = NULL;
// 	cmd = (t_cmd *)cmd_list;
// 	//this lstiter is going through cmds (t_cmd)
// 	//check the inputs
// 	ft_lstiter(cmd->input, &input_files);
// 	// ft_lstiter(cmd->output, &output_files);
// 	// execute_comand_for_real(cmd->cmd_arr, &cmd_and_flags);

// }

// void	*exec_pipe_group(void *pipe_group)
// {
// 	t_data	*data;

// 	data = (t_data *)pipe_group;
// 	//this lstiter is going through cmds (t_cmd)
// 	ft_lstiter((t_cmd *)(data->cmd_list->content), &exec_cmd);
// }


// void	kiddi_process(t_data *data)
// {
// 	// (void)data;

// 	//this lstiter is going through pipe groups 
// 	ft_lstiter(data->cmd_list, &exec_cmd);
// }
