#include "../../include/minishell.h"

void	check_builtin(t_par *p)
{
	t_list		*temp;
	t_cmd		*cmdnode;

	temp = p->cmdlist;
	while (temp)
	{
		cmdnode = temp->content;
		cmdnode->builtin = is_builtin(cmdnode);
		temp = temp->next;
	}
}

bool	is_builtinwithflag(t_par *p)
{
	t_list		*temp;
	t_cmd		*cmdnode;

	temp = p->cmdlist;
	while (temp)
	{
		cmdnode = temp->content;
		if (!cmdnode || !cmdnode->cmd_arr || !cmdnode->cmd_arr[0])
			return (false);
		if ((!ft_strncmp("pwd", cmdnode->cmd_arr[0], 4)
				|| !ft_strncmp("export", cmdnode->cmd_arr[0], 7)
				|| !ft_strncmp("unset", cmdnode->cmd_arr[0], 6)
				|| !ft_strncmp("env", cmdnode->cmd_arr[0], 4)
				|| !ft_strncmp("exit", cmdnode->cmd_arr[0], 5))
			&& cmdnode->cmd_arr[1])
			return (msg_error(cmdnode->cmd_arr[0], E_MANYARG, NULL), true);
		if (!ft_strncmp("cd", cmdnode->cmd_arr[0], 3)
			&& cmdnode->cmd_arr[1] && cmdnode->cmd_arr[2])
			return (msg_error("cd", E_MANYARG, NULL), true);
		temp = temp->next;
	}
	return (false);
}

bool	is_builtin(t_cmd *cmdnode)
{
	if (!cmdnode->cmd_arr || !cmdnode->cmd_arr[0])
		return (false);
	if (!ft_strncmp("pwd", cmdnode->cmd_arr[0], 4)
		|| !ft_strncmp("export", cmdnode->cmd_arr[0], 7)
		|| !ft_strncmp("unset", cmdnode->cmd_arr[0], 6)
		|| !ft_strncmp("env", cmdnode->cmd_arr[0], 4)
		|| !ft_strncmp("exit", cmdnode->cmd_arr[0], 5)
		|| !ft_strncmp("echo", cmdnode->cmd_arr[0], 5)
		|| !ft_strncmp("cd", cmdnode->cmd_arr[0], 3))
		return (true);
	return (false);
}
