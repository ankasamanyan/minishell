#include "../../include/minishell.h"

void	parser(t_par *p)
{
	t_list			*temp;
	t_tok			*token;
	t_cmd			*cmdnode;
	t_toktype		curr_tokentype;

	temp = p->tokenlist;
	while (temp)
	{
		token = temp->content;
		curr_tokentype = get_tokentype(p, token);
		cmdnode = handle_token(p, cmdnode, curr_tokentype, token->lexeme);
		p->prev_tokentype = curr_tokentype;
		temp = temp->next;
	}
	p->data->cmd_list = p->cmdlist;
}

/*
Adds a cmdnode at first call of function when cmdlist is still NULL.
Adds a cmndnode for each new command. Due to the limited number of operators
in the subject, this only happens after a pipe.
*/
t_cmd	*handle_token(t_par *p, t_cmd *cmdnode, t_toktype curr_tokentype,
	char *lexeme)
{
	t_pair			*redir_pair;

	if (p->cmdlist == NULL || curr_tokentype == pipe_oper)
		cmdnode = add_commandnode(p);
	if (curr_tokentype == cmdstring)
		cmdnode->cmd_arr = append_string(cmdnode->cmd_arr, lexeme);
	if (curr_tokentype & (input_redir_oper | output_redir_oper))
		redir_pair = add_redirnode(cmdnode, lexeme, curr_tokentype);
	if (curr_tokentype & (input_redir_str | output_redir_str))
	{
		if (p->prev_tokentype == input_redir_oper)
			redir_pair = ft_lstlast(cmdnode->inputlist)->content;
		if (p->prev_tokentype == output_redir_oper)
			redir_pair = ft_lstlast(cmdnode->outputlist)->content;
		redir_pair->string = lexeme;
	}
	return (cmdnode);
}

/*
Groups the token lexemes into the following categories:
operators
-	pipe operator
	-	initiates a new command node
	-	doesn't itself lead to input / output redir. The absence of
		input / output redir lets exec part know that a pipe
		connects the commands
-	input redirection operator (doesn't matter whether '<' or '<<')
-	output redirection operator (doesn't matter whether '>' or '>>')
-	redirection string (doesn't really matter whether for input or output)
command words
In the current version, there is no difference between the subcases.
They are identified automatically by their position in the char **cmd_array.
-	continuation of a command string sequence
	-	following a prior command string or
	-	following the single string after an io redirection operator
-	start of a new command string sequence.
	-	not following anything (start of input string)
	-	following a pipe
*/
int	get_tokentype(t_par *p, t_tok *token)
{
	if (token->operator)
	{
		if (!ft_strncmp(token->lexeme, "|", 2))
			return (pipe_oper);
		if (!ft_strncmp(token->lexeme, "<", 69)
			|| !ft_strncmp(token->lexeme, "<<", 420))
			return (input_redir_oper);
		return (output_redir_oper);
	}
	if (p->prev_tokentype == input_redir_oper)
		return (input_redir_str);
	if (p->prev_tokentype == output_redir_oper)
		return (output_redir_str);
	return (cmdstring);
}

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
