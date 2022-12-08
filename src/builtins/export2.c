#include "../../include/minishell.h"

/*
-	len_name is the int length of the name (the part of the env string before
	the equal sign). With that info, ft_substr can divide the string into
	the variable's name and its value.
-	init rank to -1 to show that it has not been evaluated.
	Used for alphabetizing (export with no args prints in alphabetical order)
*/
void	build_exportlistfromenv(t_data *data)
{
	int		i;
	t_exp	*expnode;
	int		len_name;

	i = 0;
	data->exp_list = NULL;
	while (data->env[i])
	{
		expnode = malloc(1 * sizeof(t_exp));
		len_name = ft_strchr(data->env[i], '=') - data->env[i];
		expnode->name = ft_substr(data->env[i], 0, len_name);
		expnode->value = ft_substr(data->env[i], len_name + 1,
				ft_strlen(data->env[i]));
		expnode->rank = -1;
		ft_lstadd_back(&data->exp_list, ft_lstnew(expnode));
		i++;
	}
	set_order(data->exp_list);
}

/*
Assigns ranks based on the alphabetical values of content.name.
while loop is terminated at lstsize -1 because the last node is
not reached during the while loop and therefore shouldn't
be included in the the while's condition count.
*/
void	set_order(t_list *list)
{
	int		i;
	t_list	*curr_ranked;
	t_list	*compare;

	reset_rank(list);
	i = 0;
	while (i < ft_lstsize(list) - 1)
	{
		curr_ranked = get_firstunranked(list);
		((t_exp *)curr_ranked->content)->rank = i;
		compare = curr_ranked->next;
		while (compare)
		{
			if (is_unrankedandprecedes(curr_ranked->content, compare->content))
			{
				((t_exp *)compare->content)->rank = i;
				((t_exp *)curr_ranked->content)->rank = -1;
				curr_ranked = compare;
			}
			compare = compare->next;
		}
		i++;
	}
	curr_ranked = get_firstunranked(list);
	((t_exp *)curr_ranked->content)->rank = i;
}

void	reset_rank(t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp)
	{
		((t_exp *)temp->content)->rank = -1;
		temp = temp->next;
	}
}

/*
Returns the first node whose content's rank value has not
been modified. This corresponds to rank = -1.
*/
t_list	*get_firstunranked(t_list *list)
{
	t_list	*temp;
	t_exp	*expnode;

	temp = list;
	while (temp)
	{
		expnode = temp->content;
		if (expnode->rank == -1)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

bool	is_unrankedandprecedes(t_exp *node1, t_exp *node2)
{
	return (node2->rank == -1
		&& ft_strncmp(node1->name, node2->name,
			ft_strlen(node1->name) + 1) > 0);
}
