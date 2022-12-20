#include "../../include/minishell.h"

void	if_no_output(t_cmd *cmd)
{
	if (cmd->outputlist == NULL)
	{
		if (ft_lstsize(cmd->data->cmd_list) == cmd->data->cmd_count)
		{
			if (cmd->fd_out > 2)
				close(cmd->fd_out);
			cmd->fd_out = STDOUT_FILENO;
		}
		else
		{
			if (cmd->fd_out > 2)
				close(cmd->fd_out);
			cmd->fd_out = cmd->data->pipe[WRITE_END];
		}
	}
}

void	output_files(void *outfile)
{
	t_pair *const	output = outfile;

	if (output->doublebracket == false)
	{
		if (output->cmd->fd_out > 2)
			close(output->cmd->fd_out);
		output->cmd->fd_out = open(output->string,
				O_WRONLY | O_TRUNC | O_CREAT, 0777);
	}
	else if (output->doublebracket == true)
	{
		if (output->cmd->fd_out > 2)
			close(output->cmd->fd_out);
		output->cmd->fd_out = open(output->string,
				O_WRONLY | O_APPEND | O_CREAT, 0777);
	}
	if (output->cmd->fd_out < 0)
	{
		output->cmd->data->file_err = true;
		err_msg(output->string, output->cmd->data);
		return ;
	}
}
