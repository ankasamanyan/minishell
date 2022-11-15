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

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	int		pid;
	t_data	data;
	t_exec	*exec;
	//alloc for env && put in struct??
	exec = data.exec; //?
	while (*env)
		if (ft_strncmp(*env++, "PATH=", 5) == 0)
			exec->big_path = (*(env - 1) + 5);
	while (ft_lstsize(data.cmd_list)) //?
	{
		pipe(exec->pipe);
		find_lil_path(exec->big_path, &data);
		if (exec->full_path == NULL)
		{
			perror(((t_cmd *)data.cmd_list->content)->cmd_arr[0]);
			exec->temp_pipe = exec->pipe[READ_PIPE];
			close(exec->pipe[WRITE_PIPE]);
			continue ;
		}
		pid = fork();
		if (pid == 0)
		{
			//kiddi_process();
		}
	}
	//fork
	// find the path to the conmmand 
	// execute the command 
	// dup to pipe 
	// find next command 
	// execute the next command 
	return 0;
}
