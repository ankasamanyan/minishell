#include "../../include/minishell.h"

bool	unset(t_cmd *cmdnode)
{
	int			i;
	t_list		*target;

	if (!cmdnode->cmd_arr[1])
		return (false);
	if (cmdnode->cmd_arr[1][0] == '-')
		return (msg_error("export", cmdnode->cmd_arr[1], E_INVALOPT), true);
	i = 1;
	while (cmdnode->cmd_arr[i])
	{
		target = get_namenode(cmdnode->data->exp_list, cmdnode->cmd_arr[i]);
		if (target)
		{
			del_fromexplist(target, cmdnode->data->exp_list);
			set_order(cmdnode->data->exp_list);
			build_env(cmdnode->data, cmdnode->data->exp_list);
			break ;
		}
		i++;
	}
	return (false);
}

/*
Deletes del_node from exp_list and restores the list continuity.
*/
void	del_fromexplist(t_list *del_node, t_list *exp_list)
{
	t_exp		*expnode;

	expnode = del_node->content;
	free(expnode->name);
	if (expnode->value)
		free(expnode->value);
	free(expnode);
	if (del_node == exp_list)
		exp_list = del_node->next;
	else if (del_node == ft_lstlast(exp_list))
		get_precedingnode(del_node, exp_list)->next = NULL;
	else
		get_precedingnode(del_node, exp_list)->next = del_node->next;
	free(del_node);
}

/*
Returns NULL if
- Passed node is first node
- Passed node is not present
Ideally, this should not happen because the calling function
tests for these cases.
*/
t_list	*get_precedingnode(t_list *node, t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp->next && temp->next != node)
		temp = temp->next;
	return (temp);
}
