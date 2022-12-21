/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ordering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:35:36 by wmardin           #+#    #+#             */
/*   Updated: 2022/12/21 16:35:36 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Assigns ranks based on the alphabetical values of content.name.
while loop is terminated at lstsize -1 because the last node is
not reached during the while loop and therefore shouldn't
be included in the the while's condition count.
*/
void	set_order(t_list *list)
{
	int		i;

	if (!list)
		return ;
	reset_rank(list);
	i = 0;
	while (i < ft_lstsize(list) - 1)
	{
		compare_nodes(list, i);
		++i;
	}
	((t_exp *)get_firstunranked(list)->content)->rank = i;
}

void	compare_nodes(t_list *list, int i)
{
	t_list	*curr_ranked;
	t_list	*compare;

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
