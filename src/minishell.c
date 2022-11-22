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

void	input_files(void *input)
{
	t_twople	*twople;
	char		**stringy;

	twople = (t_twople *)input;
	if (twople->second_sign == false)
	{
		if (access(twople->filename, F_OK) != 0)
			perror("Minishell😿:");
		else if (access(twople->filename, R_OK) != 0)
			perror("Minishell😿:");
		if (twople == NULL)
			twople->data->temp_pipe = open(twople->filename, O_RDONLY);
	}
	if (twople->second_sign == true)
	{
		while (42)
		{
			stringy = readline("> ");
			if ((ft_strncmp(stringy, twople->filename, ft_strlen(twople->filename)) == 0)
				&& (stringy[ft_strlen(twople->filename)] == '\n'))
				break ;
			else
				write(twople->data->temp_pipe, stringy, ft_strlen(stringy)); // ???
			free(stringy);
		}
		free(stringy);
	}
}

// void	execute_comand_for_real()
// {
// 	// dup
// 	// close (temp_pipe[read])
// 	// execve
// }

void	exec_cmd(void *cmd_list)
{
	t_cmd	*cmd;

	// cmd = NULL;
	cmd = (t_cmd *)cmd_list;
	//this lstiter is going through cmds (t_cmd)
	//check the inputs
	ft_lstiter(cmd->input, &input_files);
	// ft_lstiter(cmd->output, &output_files);
	// execute_comand_for_real(cmd->cmd_arr, &cmd_and_flags);

}

// void	*exec_pipe_group(void *pipe_group)
// {
// 	t_data	*data;

// 	data = (t_data *)pipe_group;
// 	//this lstiter is going through cmds (t_cmd)
// 	ft_lstiter((t_cmd *)(data->cmd_list->content), &exec_cmd);
// }


void	kiddi_process(t_data *data)
{
	// (void)data;

	//this lstiter is going through pipe groups 
	ft_lstiter(data->cmd_list, &exec_cmd);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;

	int		pid;
	t_data	data;
	t_exec	*exec;

	
	
	//fork
	// find the path to the conmmand 
	// execute the command 
	// dup to pipe 
	// find next command 
	// execute the next command 
	return 0;
}
