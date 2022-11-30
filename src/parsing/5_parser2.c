#include "../../include/minishell.h"

t_cmd	*add_commandnode(t_par *p)
{
	t_cmd	*cmdnode;

	cmdnode = malloc(1 * sizeof(t_cmd));
	cmdnode->cmd_arr = NULL;
	cmdnode->inputlist = NULL;
	cmdnode->outputlist = NULL;
	cmdnode->fd_in = 0;
	cmdnode->fd_out = 1;
	cmdnode->data = p->data;
	ft_lstadd_back(&p->cmdlist, ft_lstnew(cmdnode));
	return (cmdnode);
}

t_pair	*add_redirnode(t_cmd *cmdnode, char *operator, t_toktype tokentype)
{
	t_pair	*redir_pair;

	redir_pair = malloc (1 * sizeof(t_pair));
	redir_pair->doublebracket = ft_strlen(operator) == 2;
	redir_pair->cmd = cmdnode;
	if (tokentype == input_redir_oper)
		ft_lstadd_back(&cmdnode->inputlist, ft_lstnew(redir_pair));
	else
		ft_lstadd_back(&cmdnode->outputlist, ft_lstnew(redir_pair));
	return (redir_pair);
}
