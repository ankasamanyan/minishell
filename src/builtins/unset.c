#include "../../include/minishell.h"

bool	unset(t_cmd *cmdnode)
{
	int		i;
	bool	match;

	if (!cmdnode->cmd_arr[1])
		return (false);
	if (cmdnode->cmd_arr[1][0] == '-')
		return (msg_error("export", cmdnode->cmd_arr[1], E_INVALOPT), true);
	i = 1;
	while (cmdnode->cmd_arr[i])
	{
		match = has_namematch(cmdnode->cmd_arr[i], cmdnode->data->exp_list);
		i++;
	}
	if (match)
	{
		set_order(cmdnode->data->exp_list);
		build_env(cmdnode->data, cmdnode->data->exp_list);
	}
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
			printf("name found\n");
			free(expnode->name);
			if (expnode->value)
				free(expnode->value);
			free(expnode);
			if (temp == exp_list)
			{
				exp_list = temp->next;
				free(temp);
			}
			else if (temp == ft_lstlast(exp_list))
			{
				get_precedingnode(temp, exp_list)->next = NULL;
				free(temp);
			}
			else
			{
				get_precedingnode(temp, exp_list)->next = temp->next;
			}
			return (true);
		}
		temp = temp->next;
	}
	return (false);
}

/*
Returns NULL if
- Passed node is first node
- Passed node is not present
*/
t_list	*get_precedingnode(t_list *node, t_list *list)
{
	t_list	*temp;

	temp = list;
	while(temp->next && temp->next != node)
		temp = temp->next;
	return(temp);
}
