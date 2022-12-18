#include "../../include/minishell.h"

void	print_export(t_list *list)
{
	int			i;
	t_list		*temp;
	t_exp		*expnode;

	i = 0;
	while (i < ft_lstsize(list))
	{
		temp = list;
		while (((t_exp *)temp->content)->rank != i)
			temp = temp->next;
		expnode = temp->content;
		//WOLF PLS HALP WE NEED TO FIX THIS OMG W EAER E DIYNG
		printf("declare -x %s", expnode->name);
		if (expnode->value)
			printf("=\"%s\"", expnode->value);
		printf("\n");
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
