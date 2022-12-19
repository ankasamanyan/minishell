#include "../../include/minishell.h"

void	print_export(t_cmd *cmdnode)
{
	int			i;
	t_list		*temp;
	t_exp		*expnode;

	i = 0;
	while (i < ft_lstsize(cmdnode->data->exp_list))
	{
		temp = cmdnode->data->exp_list;
		while (((t_exp *)temp->content)->rank != i)
			temp = temp->next;
		expnode = temp->content;
		ft_putstr_fd("declare -x ", cmdnode->fd_out);
		ft_putstr_fd(expnode->name, cmdnode->fd_out);
		if (expnode->value)
		{
			ft_putstr_fd("=\"", cmdnode->fd_out);
			ft_putstr_fd(expnode->value, cmdnode->fd_out);
			ft_putstr_fd("\"", cmdnode->fd_out);
		}
		ft_putstr_fd("\n", cmdnode->fd_out);
		i++;
	}
}

void	increase_shlvl(t_data *data)
{
	t_list		*node;
	t_exp		*content;
	char		*temp;

	node = get_namenode(data->exp_list, "SHLVL");
	if (!node)
		return ;
	content = node->content;
	if (!content->value)
	{
		content->value = ft_strdup("1");
		return ;
	}
	temp = content->value;
	content->value = ft_itoa(ft_atoi(content->value) + 1);
	free (temp);
}
