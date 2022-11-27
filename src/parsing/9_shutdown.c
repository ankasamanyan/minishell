#include "../../include/minishell.h"

void	del_tokenlistnode(t_list *listnode)
{
	t_tok		*tokennode;

	//set next of beforelast to null
	tokennode = listnode->content;
	free(tokennode->lexeme);
	free(listnode->content);
	free(listnode);
}
