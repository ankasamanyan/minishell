/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_shutdown2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:06:10 by wmardin           #+#    #+#             */
/*   Updated: 2022/12/20 14:06:10 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	del_explist(t_list *list)
{
	t_list		*temp;
	t_exp		*exp;

	while (list)
	{
		exp = list->content;
		if (exp->name)
			free(exp->name);
		if (exp->value)
			free(exp->value);
		free(exp);
		temp = list;
		list = list->next;
		free(temp);
	}
}
