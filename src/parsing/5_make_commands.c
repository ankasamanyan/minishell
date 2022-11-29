#include "../../include/minishell.h"

/*
Casts the t_list to token.
Checks what type of token it is. This is a mix of content evaluation and
machine state.
If cmdlist has no node, puts one. This is only the case in the first call.
Might move this out, into init.
*/
t_list	*make_commands(t_list *list, t_par *p)
{
	t_tok			*token;
	static t_cmd	*cmdnode;
	t_pair			*redir_pair;
	t_toktype		type_currenttoken;

	if (!list->content)
		return (NULL);
	token = list->content;
	type_currenttoken = get_tokentype(p, token);
	if (p->cmdlist == NULL)
		cmdnode = add_commandnode(p);
	if (type_currenttoken == newcmd)
	{
		if (p->prev_token != init_tok)
			cmdnode = add_commandnode(p);
		cmdnode->cmd_arr = append_string(cmdnode->cmd_arr, token->lexeme);
	}
	if (type_currenttoken == cmdstring)
	{
		cmdnode->cmd_arr = append_string(cmdnode->cmd_arr, token->lexeme);
	}
	if (type_currenttoken & (input_redir_oper | output_redir_oper))
	{
		redir_pair = malloc (1 * sizeof(t_pair));
		redir_pair->doublebracket = ft_strlen(token->lexeme) == 2;
		redir_pair->cmd = cmdnode;
		if (type_currenttoken == input_redir_oper)
			ft_lstadd_back(&cmdnode->inputlist, ft_lstnew(redir_pair));
		else
			ft_lstadd_back(&cmdnode->outputlist, ft_lstnew(redir_pair));
	}
	if (type_currenttoken & (input_redir_str | output_redir_str))
	{
		if (p->prev_token == input_redir_oper)
			redir_pair = ft_lstlast(cmdnode->inputlist)->content;
		else if (p->prev_token == output_redir_oper)
			redir_pair = ft_lstlast(cmdnode->outputlist)->content;
		redir_pair->string = token->lexeme;
	}
	p->prev_token = type_currenttoken;
	return (list->next);
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
	if (p->prev_token == input_redir_oper)
		return (input_redir_str);
	if (p->prev_token == output_redir_oper)
		return (output_redir_str);
	if (p->prev_token & (newcmd | cmdstring | input_redir_str))
		return (cmdstring);
	return (newcmd);
}

/*
Appends a string to a string array.
If the string array doesn't exist yet,
makes a new string array with the string as only content.
Frees the passed string array.
*/
char	**append_string(char **array, char *string)
{
	char	**result;
	int		i;

	if (!array)
	{
		result = malloc(2 * sizeof(char *));
		result[0] = string;
		result[1] = NULL;
		return (result);
	}
	i = 0;
	while (array[i])
		i++;
	result = malloc((i + 2) * sizeof(char *));
	i = 0;
	while (array[i])
	{
		result[i] = array[i];
		i++;
	}
	result[i] = string;
	i++;
	result[i] = NULL;
	free(array);
	return (result);
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
