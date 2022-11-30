#include "../../include/minishell.h"

void	shutdown(t_data *data)
{
	t_par	*p;

	p = &data->parsing_struct;
	del_tokenlist(p->tokenlist);
	del_cmdlist(p->cmdlist);
	free(p->input);
}

void	del_tokenlist(t_list *list)
{
	t_list		*temp1;
	t_list		*temp2;
	t_tok		*token;

	temp1 = list;
	while (temp1)
	{
		if (temp1->content)
		{
			token = temp1->content;
			if (token->lexeme)
				free(token->lexeme);
			free(token);
		}
		temp2 = temp1;
		temp1 = temp1->next;
		free(temp2);
	}
}

/*
Doesn't free the char *, only the char **. The char *
are freed in del_tokenlist.
*/
void	del_cmdlist(t_list *list)
{
	t_list		*temp;
	t_cmd		*cmdnode;

	while (list)
	{
		cmdnode = list->content;
		if (cmdnode->cmd_arr)
			free(cmdnode->cmd_arr);
		del_pairlist(cmdnode->inputlist);
		del_pairlist(cmdnode->outputlist);
		free(cmdnode);
		temp = list;
		list = list->next;
		free(temp);
	}
}

/*
The pointer to the allocated string in pair.string points
to the string from tokenlist. It doesn't get freed here
because it gets freed in del_tokenlist.

*/
void	del_pairlist(t_list *list)
{
	t_list		*temp;
	t_pair		*pair;

	while (list)
	{
		pair = list->content;
		free(pair);
		temp = list;
		list = list->next;
		free(temp);
	}
}
