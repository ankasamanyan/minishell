#include "../../include/minishell.h"

void	print_2d_array(char	**arr, int fd)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i] != NULL)
		{
			ft_putstr_fd(arr[i], fd);
			if (arr[i][ft_strlen(arr[i]) - 1] != '\n')
				ft_putchar_fd('\n', fd);
			i++;
		}
	}
}

void	find_cmd_path(char *big_path, t_cmd *cmd)
{
	char	**smoll_pathsies;
	char	*path;
	int		i;

	i = 0;
	smoll_pathsies = ft_split(big_path, ':');
	cmd->data->big_path = NULL;
	while (smoll_pathsies[i])
	{
		path = ft_triple_strjoin(smoll_pathsies[i++],
				"/", cmd->cmd_arr[0]);
		if (access(path, X_OK) == 0)
		{
			cmd->data->full_path = path;
			return ;
		}
		else if (access(path, F_OK) == 0)
		{
			free(path);
			cmd->data->exitcode = 126;
		}
		else
		{
			cmd->data->exitcode = 127;
			free(path);
		}
	}
	if (access(cmd->cmd_arr[0], X_OK) == 0)
	{
		cmd->data->full_path = ft_strdup(cmd->cmd_arr[0]);
		return ;
	}
	else
	{
		cmd->data->exitcode = 126;
		access(cmd->cmd_arr[0], F_OK);
	}
	cmd->data->exitcode = 127;
	ft_free_array(smoll_pathsies);
	perror(cmd->cmd_arr[0]);
}

void	kiddi_process(t_cmd *cmd)
{
	// printf("%s\tbefore the dups  fd_in = %d   fd_out = %d \n%s",SKY, cmd->fd_in, cmd->fd_out, RESET);
	// printf("%s\tbefore the dups  pipe[WRITE] = %d   pipe[READ] = %d \n%s", SKY, cmd->data->pipe[WRITE_END], cmd->data->pipe[READ_END], RESET);
	// printf("%s\tbefore the dups  temp_pipe = %d \n%s", SKY, cmd->data->temp_pipe, RESET);
	if (cmd->fd_in > 2)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out > 2)
		dup2(cmd->fd_out, STDOUT_FILENO);
	// print_2d_array(cmd->cmd_arr, 2);
	// printf("full path before execve: %s\n",cmd->data->full_path);
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
	// if (cmd->data->pipe[READ_END] > 2)
	// 	close(cmd->data->pipe[READ_END]);
	// if (cmd->data->pipe[WRITE_END] > 2)
	// 	close(cmd->data->pipe[WRITE_END]);
	// printf("%s pipe[READ_END] from exec: %i\n%s", RED, cmd->data->pipe[READ_END], RESET);
	// printf("%s pipe[WRITE_END] from exec: %i\n%s", RED, cmd->data->pipe[WRITE_END], RESET);
	// printf("%s\n", RESET);
	pipe(cmd->data->pipe);
	// printf("%s    das ist pipe[READ_END] from exec: %i\n%s", PINK, cmd->data->pipe[READ_END], RESET);
	// printf("%s    das ist pipe[WRITE_END] from exec: %i\n%s", PINK, cmd->data->pipe[WRITE_END], RESET);
	// printf("%sbefore the dups  temp_pipe = %d \n%s", PINK, cmd->data->temp_pipe, RESET);
	// printf("%s\n", RESET);
	cmd->data->cmd_count++;
			// printf("before no input func\n");
	if_no_input(cmd);
			// printf("after no input func\n start the ft_lstiter on inputs\n");
	ft_lstiter(cmd->inputlist, &input_files); //input checks
	if_no_output(cmd);
			// printf("start the ft_lstiter on outputs\n");
	ft_lstiter(cmd->outputlist, &output_files); //output checks
			// printf("after no ft_lstiter on outputs\n start no output func\n");
			// printf("after no output func\n");
			// printf("find PATH in env");
	search_path_env(cmd); //find PATH in env
			// printf(" results into: %s\n", cmd->data->big_path);
			// printf("find executable of cmd\n");
	find_cmd_path(cmd->data->big_path, cmd); //find executable of cmd
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
		int tmp;
		// waitpid(cmd->data->pid, &(cmd->data->exitcode), 0);
		waitpid(cmd->data->pid, &tmp, 0);
		cmd->data->exitcode = tmp;

		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		if (cmd->data->pipe[WRITE_END] > 2)
			close(cmd->data->pipe[WRITE_END]);
		if (cmd->data->temp_pipe > 2)
			close(cmd->data->temp_pipe);
		cmd->data->temp_pipe = cmd->data->pipe[READ_END];
		// if (cmd->data->pipe[READ_END] > 2)
		// 	close(cmd->data->pipe[READ_END]);
		// printf("%s    das ist pipe[READ_END] from parent: %i\n%s", PINK, cmd->data->pipe[READ_END], RESET);
		// printf("%s    das ist pipe[WRITE_END] from exec: %i\n%s", PINK, cmd->data->pipe[WRITE_END], RESET);
		// printf("%s\tbefore the dups  temp_pipe = %d \n%s", PINK, cmd->data->temp_pipe, RESET);
		
		// printf("Hi, after parent\n");
		if(cmd->data->cmd_count == ft_lstsize(cmd->data->cmd_list) + 1)
			close(cmd->data->temp_pipe);

		// waitpid(-1, &(cmd->data->exitcode), WNOHANG); // innit thisssssssssssssssss




		// close(cmd->data->pipe[WRITE_END]); // close pipe[write]	
	}
}

