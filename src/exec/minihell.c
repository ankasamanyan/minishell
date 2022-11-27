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
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->fd_out, STDOUT_FILENO);
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
	printf("called exec, %s\n", cmd->cmd_arr[0]);
	cmd->data->cmd_count++;
	if_no_input(cmd);
	ft_lstiter(cmd->inputlist, &input_files); //input checks
	ft_lstiter(cmd->outputlist, &output_files); //output checks
	if_no_output(cmd);
	search_path_env(cmd); //find PATH in env
	find_cmd_path(cmd->data->big_path, cmd->data); //find executable of cmd
	cmd->data->pid = fork();
	if (cmd->data->pid == 0)
		kiddi_process(cmd);
	else
	{
		waitpid(-1, NULL, WNOHANG);



		// waitpid(-1, &(cmd->data->exitcode), WNOHANG); // innit thisssssssssssssssss




		// close(cmd->data->pipe[WRITE_END]); // close pipe[write]	
	}

}