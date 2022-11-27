#include "../../include/minishell.h"

/*
This function helps to determine what to do with a char.
The decision is based on what type of char the current
char is vs. what type the previous char was.
There are 4 different char categories (dollar, whitespace,
operator, and word).
If quotation is active, all chars are handled as wordchars, except
for $ that can be used for expansion.
$ cases:
-	a $ at the end of a token is treated by bash as a normal char
-	a $ followed by a quotation marker is erased and only the quoted chars
	are kept
*/
int	get_chartype(t_par *p, char c)
{
	if (c == '$' && !p->single_quoted)
		return (dollar);
	if (p->double_quoted || p->single_quoted)
		return (word);
	if (is_whitespace(c))
		return (whitespace);
	if (is_operatorchar(c))
		return (operator);
	else
		return (word);
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
