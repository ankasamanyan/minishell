#include "../../include/minishell.h"

void	parse_commands(t_par *p)
{
	t_list			*temp;
	t_tok			*token;
	static t_cmd	*cmdnode;
	t_toktype		curr_tokentype;

	temp = p->tokenlist;
	while (temp)
	{
		token = temp->content;
		curr_tokentype = get_tokentype(p, token);
		cmdnode = handle_cmdnode(p, cmdnode, curr_tokentype, token->lexeme);
		handle_redirnode(p, cmdnode, curr_tokentype, token->lexeme);
		p->prev_tokentype = curr_tokentype;
		//return (tokenlist->next);
		temp = temp->next;



		//temp = make_commands(temp, p);
	}
	p->data->cmd_list = p->cmdlist;
}

/*
The decision tree is distributed over the "handle" functions.
*/
t_list	*make_commands(t_list *tokenlist, t_par *p)
{
	t_tok			*token;
	static t_cmd	*cmdnode;
	t_toktype		curr_tokentype;

	/* if (!tokenlist->content)
		return (NULL); */
	token = tokenlist->content;
	curr_tokentype = get_tokentype(p, token);
	cmdnode = handle_cmdnode(p, cmdnode, curr_tokentype, token->lexeme);
	handle_redirnode(p, cmdnode, curr_tokentype, token->lexeme);
	p->prev_tokentype = curr_tokentype;
	return (tokenlist->next);
}

t_cmd	*handle_cmdnode(t_par *p, t_cmd *cmdnode, t_toktype curr_tokentype,
	char *lexeme)
{
	if (p->cmdlist == NULL)
		cmdnode = add_commandnode(p);
	if (curr_tokentype == newcmd)
	{
		if (p->prev_tokentype != init_tok)
			cmdnode = add_commandnode(p);
		cmdnode->cmd_arr = append_string(cmdnode->cmd_arr, lexeme);
	}
	if (curr_tokentype == cmdstring)
		cmdnode->cmd_arr = append_string(cmdnode->cmd_arr, lexeme);
	return (cmdnode);
}

void	handle_redirnode(t_par *p, t_cmd *cmdnode, t_toktype curr_tokentype,
	char *lexeme)
{
	t_pair			*redir_pair;

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
}

/*
Groups the token lexemes into the following categories:
operators
-	pipe operator
	-	isn't ever specifically checked for, because in our project, a pipe
		means that no input or output redirection nodes are created. If both
		nodes are missing, exec part knows that a pipe connects the commands.
-	input redirection operator (doesn't matter whether '<' or '<<')
-	output redirection operator (doesn't matter whether '>' or '>>')
-	redirection string (doesn't matter whether for input or output)
commands
-	continuation of a command string sequence
	-	following a prior command string or
	-	following the single string after an input redirection operator
	-	but not following the single string after an output redir operator
-	start of a new command string sequence
	-	not following anything or
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
	if (p->prev_tokentype & (newcmd | cmdstring | input_redir_str))
		return (cmdstring);
	return (newcmd);
}
