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
