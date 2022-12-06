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

void	find_cmd_path(t_cmd *cmd)
{
	char	**smoll_pathsies;
	char	*lil_path;
	int		i;

	i = 0;
	if (cmd->cmd_arr)
	{
		smoll_pathsies = ft_split(cmd->data->big_path, ':');
		cmd->data->full_path = NULL;
		while (smoll_pathsies[i])
		{
			lil_path = ft_triple_strjoin(smoll_pathsies[i++],
					"/", cmd->cmd_arr[0]);
			if (access(lil_path, X_OK) == 0)
				cmd->data->full_path = lil_path;
			else
			{
				cmd->data->exitcode = 126;
				if (access(lil_path, F_OK))
					cmd->data->exitcode++;
				free(lil_path);
			}
		}
		if (access(cmd->cmd_arr[0], X_OK) == 0)
			cmd->data->full_path = ft_strdup(cmd->cmd_arr[0]);
		else
			access(cmd->cmd_arr[0], F_OK);
		ft_free_array(smoll_pathsies);
	}
	else
		cmd->data->full_path = NULL;
}

void	kiddi_process(t_cmd *cmd)
{
	if (cmd->fd_in > 2)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out > 2)
		dup2(cmd->fd_out, STDOUT_FILENO);
	// print_2d_array(cmd->cmd_arr, 2);
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
		if (ft_strncmp(cmd->data->env[i], "PATH=", 5) == 0)
			cmd->data->big_path = (cmd->data->env[i] + 5);
		i++;
	}
}

void	exec(void *cmd_list)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmd_list;
	pipe(cmd->data->pipe);
	cmd->data->cmd_count++;
	if_no_input(cmd);
	ft_lstiter(cmd->inputlist, &input_files); //input checks
	if_no_output(cmd);
	ft_lstiter(cmd->outputlist, &output_files); //output checks
	search_path_env(cmd); //find PATH in env
	find_cmd_path(cmd); //find executable of cmd
	//function thingy if builtin
	//if no cmd
	if (cmd->cmd_arr)
	{
		cmd->data->pid = fork();
		if (cmd->data->pid == 0)
			kiddi_process(cmd);
		else
		{
			int tmp;
			waitpid(cmd->data->pid, &tmp, 0);
			cmd->data->exitcode = tmp;
			free(cmd->data->full_path);
			if (cmd->fd_in > 2)
				close(cmd->fd_in);
			if (cmd->fd_out > 2)
				close(cmd->fd_out);
			if (cmd->data->pipe[WRITE_END] > 2)
				close(cmd->data->pipe[WRITE_END]);
			if (cmd->data->temp_pipe > 2)
				close(cmd->data->temp_pipe);
			cmd->data->temp_pipe = cmd->data->pipe[READ_END];
			if(cmd->data->cmd_count == ft_lstsize(cmd->data->cmd_list) + 1)
				close(cmd->data->temp_pipe);
		}
	}
}

