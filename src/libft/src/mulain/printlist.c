/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:31:48 by wmardin           #+#    #+#             */
/*   Updated: 2022/11/18 20:53:53 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prints the NULL terminated linked list <list> of standard libft type.
Assumes that <list.content> is a char *.
Pass <title> to insert an identifier in the box around the list contents.
"┌" -> char[4]
"┐" -> char[4]
"│" -> char[4]
"─" -> char[4]
"a" -> char[2]
They all take up 2 more than a normal char.
*/
void	printlist_str(t_list *list, char *title)
{
	t_list	*temp;
	int		len_title;
	int		len_line;

	if (!title)
		title = "─";
	temp = list;
	len_title = ft_printf("┌────%s────┐\n", title) - 10 * 2;
	while (temp)
	{
		len_line = ft_printf("│ %s", (char *)temp->content) - 1 * 2;
		while (len_line++ < len_title - 2)
			ft_printf(" ");
		if (len_line == len_title - 1)
			ft_printf("│\n");
		else
			ft_printf("\n");
		temp = temp->next;
	}
	len_line = 0;
	ft_printf("└");
	while (len_line++ < len_title - 3)
		ft_printf("─");
	ft_printf("┘\n");
}
