#include "../../include/minishell.h"

void	path_access(t_cmd *cmd, char **smoll_pathsies)
{
	char	*lil_path;
	int		i;

	i = 0;
	while (smoll_pathsies[i])
	{
		lil_path = ft_triple_strjoin(smoll_pathsies[i++],
				"/", cmd->cmd_arr[0]);
		if (access(lil_path, X_OK) == 0)
		{
			cmd->data->full_path = lil_path;
			cmd->data->halp = true;
			return ;
		}
		else
			free(lil_path);
	}
}

void	find_cmd_path(t_cmd *cmd)
{
	char	**smoll_pathsies;
	int		aaaaa;

	aaaaa = 1;
	cmd->data->halp = false;
	if (cmd->cmd_arr)
	{
		smoll_pathsies = ft_split(cmd->data->big_path, ':');
		cmd->data->full_path = NULL;
		path_access(cmd, smoll_pathsies);
		if (access(cmd->cmd_arr[0], X_OK) == 0)
		{
			cmd->data->full_path = ft_strdup(cmd->cmd_arr[0]);
			cmd->data->halp = true;
		}
		else
		{
			if (access(cmd->cmd_arr[0], F_OK) == 0)
				aaaaa = 2;
		}
		ft_free_array(smoll_pathsies);
		if (!cmd->data->halp)
			err_cmd_not_found(cmd->cmd_arr[0], aaaaa, cmd->data);
	}
}

void	kiddi_process(t_cmd *cmd)
{
	if (cmd->data->file_err)
		exit (0);
	if (cmd->fd_in > 2)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out > 2)
		dup2(cmd->fd_out, STDOUT_FILENO);
	execve(cmd->data->full_path, cmd->cmd_arr, cmd->data->env);
	perror("Minishell: Execve error");
	exit(-1);

}

void	search_path_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	if(cmd->data->big_path)
		free(cmd->data->big_path);
	while (cmd->data->env[i])
	{
		if (ft_strncmp(cmd->data->env[i], "PATH=", 5) == 0)
		{
			cmd->data->big_path = ft_strdup(cmd->data->env[i] + 5);
			break ;
		}
		i++;
	}
	if(!cmd->data->env[i])
		cmd->data->big_path = ft_strdup("");
}

void	exec(void *cmd_list)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmd_list;
	cmd->data->cmd_count++;
	cmd->data->file_err = false;
	cmd->data->exitcode = 0;
	pipe(cmd->data->pipe);
	// printf("exit code thingyyyyyyyyyy: %i\n", cmd->data->exitcode);
	if_no_input(cmd);
	ft_lstiter(cmd->inputlist, &input_files); //input checks
	if_no_output(cmd);
	ft_lstiter(cmd->outputlist, &output_files); //output checks
	// printf("exit code thingyyyyyyyyyy: %i\n", cmd->data->exitcode);
	if (cmd->data->exitcode != 0)
		return ;
	search_path_env(cmd); //find PATH in env
	if (cmd->builtin)
		builtins_exec(cmd);
	else
		pipex(cmd);
	close_them_all(cmd);
}

void	pipex(t_cmd *cmd)
{
	find_cmd_path(cmd); //find executable of cmd
	// fprintf(stderr, "exit code is %d\n", cmd->data->exitcode);
	if (cmd->cmd_arr)
	{
		if (!cmd->data->halp)
			return ;
		if (ft_strncmp((cmd->cmd_arr[0]) + (ft_strlen(cmd->cmd_arr[0]) - 9), "minishell", 10) == 0)
			setup_parent_signals();
		else
			exec_parent();
		cmd->data->pid = fork();
		if (cmd->data->pid == 0 && cmd->builtin == false)
			kiddi_process(cmd);
		else
		{
			if(cmd->data->exitcode)
				waitpid(cmd->data->pid, &cmd->data->exitcode, 0);
			else
				waitpid(cmd->data->pid, NULL, 0);
			smth_cedric_needs();
			free(cmd->data->full_path);
			cmd->data->full_path = NULL;
		}
	}
}

void	close_them_all(t_cmd *cmd)
{
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
