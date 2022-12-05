#include "../../include/minishell.h"

/*
echo should be handled differently because it should only be treated
as a builtin if it has flag -n. Other cases can get executed normally via
execve. See file in builtins for more.
cd also needs different treatment, because it takes exactly on argument.
Solution could be to implement a check for a builtin in exec part.
if builtin
	call our function
else
	execve
if builtin could be a copypaste of the test below without arr[1] part.
Could all be one big if but that would be even less readable...
*/
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

