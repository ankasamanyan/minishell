#include "../../include/minishell.h"

bool	unset(t_cmd *cmdnode)
{
	int		i;

	if (!cmdnode->cmd_arr[1])
		return (false);
	if (cmdnode->cmd_arr[1][0] == '-')
		return (msg_error("export", cmdnode->cmd_arr[1], E_INVALOPT), true);
	i = 0;
	while (cmdnode->cmd_arr[i])
	{
		if (!ft_strncmp(cmdnode->cmd_arr[i], ) - cmdnode->cmd_arr[i]);
		if (!has_invalidformat(name))
			add_expnode(cmdnode->data->exp_list, cmdnode->cmd_arr[i],
				&cmdnode->data->env);
		else
			msg_err_quote("export", cmdnode->cmd_arr[i], E_NOTVALID);
		free(name);
		i++;
	}
	set_order(cmdnode->data->exp_list);
	return (false);
}

/*
Checks if the passed string matches an export variable name.
If so, deletes that node and restores the list continuity.
Returns true
*/
bool	has_namematch(char *name, t_list *exp_list)
{
	t_list	*temp;
	t_exp	*expnode;

	temp = exp_list;
	while (temp)
	{
		expnode = temp->content;
		if (!ft_strncmp(expnode->name, name, ft_strlen(name) + 1))
		{
			free(expnode->name);
			if (expnode->value)
				free(expnode->value);
			free(expnode);
			if (temp = exp_list)
			{
				exp_list = temp->next;
				free(temp);
		}
		temp = temp->next;
	}
}