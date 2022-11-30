#include "../../include/minishell.h"

void	find_cmd_path(char *big_path, t_data *data)
{
	char	**smoll_pathsies;
	char	*lil_path;
	t_cmd	*cmd_w_flags;
	int		i;

	i = 0;
	cmd_w_flags = (t_cmd *)data->cmd_list->content;
	smoll_pathsies = ft_split(big_path, ':');
	data->full_path = NULL;
	while (smoll_pathsies[i])
	{
		lil_path = ft_triple_strjoin(smoll_pathsies[i++],
				"/", cmd_w_flags->cmd_arr[0]);
		if (access(lil_path, X_OK) == 0)
			data->full_path = lil_path;
		else
		{
			access(lil_path, F_OK);
			free(lil_path);
		}
	}
	if (access(cmd_w_flags->cmd_arr[0], X_OK) == 0)
		data->full_path = ft_strdup(cmd_w_flags->cmd_arr[0]);
	else
		access(cmd_w_flags->cmd_arr[0], F_OK);
	ft_free_array(smoll_pathsies);
}

void	kiddi_process(t_cmd *cmd)
{
	printf("before the dups  fd_in = %d   fd_out = %d \n", cmd->fd_in, cmd->fd_out);
	if (cmd->fd_in > 2)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_in > 2)
		dup2(cmd->fd_out, STDOUT_FILENO);
	printf("full path before execve: %s\n",cmd->data->full_path);
	execve(cmd->data->full_path, cmd->cmd_arr, cmd->data->env);
	perror("Minishell: Execve error");
	exit(-1);
}

void	search_path_env(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->data->env[i])
	{
		// if (ft_strncmp(cmd->data->env[i], "SHLVL=", 6) == 0)
		// 	cmd->data->shell_lvl = (ft_atoi(cmd->data->env[i] + 6));
		if (ft_strncmp(cmd->data->env[i], "PATH=", 5) == 0)
			cmd->data->big_path = (cmd->data->env[i] + 5);
		i++;
	}
}

void	exec(void *cmd_list)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmd_list;
			// printf("\n\n\n");
			// printf("exec function start, cmd: %s\n", cmd->cmd_arr[0]);
			// printf("\n\n\n");
	pipe(cmd->data->pipe);

	cmd->data->cmd_count++;
			// printf("before no input func\n");
	if_no_input(cmd);
			// printf("after no input func\n start the ft_lstiter on inputs\n");
	ft_lstiter(cmd->inputlist, &input_files); //input checks
			// printf("start the ft_lstiter on outputs\n");
	ft_lstiter(cmd->outputlist, &output_files); //output checks
			// printf("after no ft_lstiter on outputs\n start no output func\n");
	if_no_output(cmd);
			// printf("after no output func\n");
			// printf("find PATH in env");
	search_path_env(cmd); //find PATH in env
			// printf(" results into: %s\n", cmd->data->big_path);
			// printf("find executable of cmd\n");
	find_cmd_path(cmd->data->big_path, cmd->data); //find executable of cmd
			// printf("fork\n");
	cmd->data->pid = fork();
	if (cmd->data->pid == 0)
	{
		// printf("Hi, from the kiddi\n");
		kiddi_process(cmd);
		// printf("%sHi, after the kiddi%s\n", RED, RESET);
	}
	else
	{
		// printf("Hi, from parent\n");
		waitpid(cmd->data->pid, NULL, 0);
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		if (cmd->data->pipe[WRITE_END] > 2)
			close(cmd->data->pipe[WRITE_END]);
		if (cmd->data->pipe[READ_END] > 2)
			close(cmd->data->pipe[READ_END]);
		
		// printf("Hi, after parent\n");



		// waitpid(-1, &(cmd->data->exitcode), WNOHANG); // innit thisssssssssssssssss




		// close(cmd->data->pipe[WRITE_END]); // close pipe[write]	
	}

}