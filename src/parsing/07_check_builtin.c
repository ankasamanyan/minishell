#include "../../include/minishell.h"

/*
Checks for presence of a builtin and sets the builtin bool
accordingly.
*/
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

/*
The builtin "exit" will never actually get here in the current
structure. It is still tested for to make this function adaptable
for potential changes.
*/
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
