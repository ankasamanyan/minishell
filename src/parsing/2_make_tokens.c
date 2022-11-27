#include "../../include/minishell.h"

/*
-	Checks and sets qotation
-	Stores / updates the type of the current char in current_chartype
	for each iteration
-	Bitwise evaluates the type of current char to the machine state
	-	If it is compatible (char belongs to same state as current state or
		state is inititation state)
		- 	Checks if char is printable
				- Appends if printable
		-	Updates state
- 	If current char is not compatible to current machine state
	-	Finalizes current token
	-	Stores current char in static var "token"
	-	returns input + i + 1 to calling function which will call this function
		again, but at the following char.
- 	When there is no more input left
	-	Adds token if it has content and returns null, breaking the while in
		the main function.
*/
char	*make_tokens(char *input, t_par *p)
{
	int				i;
	char			*lexeme;
	t_chartype		current_chartype;

	i = 0;
	lexeme = NULL;
	while (input[i])
	{
		check_quotation(input[i], p);
		current_chartype = get_chartype(p, input[i]);
		if (is_sametoken(p, current_chartype))
		{
			if (is_tokenpart(p, input[i]))
				lexeme = append_char(lexeme, input[i]);
			p->prev_chartype = current_chartype;
		}
		else
		{
			add_tokennode(p, lexeme);
			p->prev_chartype = current_chartype;
			return (input + i);
		}
		i++;
	}
	add_tokennode(p, lexeme);
	return (NULL);
}

/*
Only checks for mode adapting, not whether the quote should
get printed.
If the other quotation mark is not active: flips status of
detected quotation mark.
*/
void	check_quotation(char c, t_par *p)
{
	if (c == '\'' && !p->double_quoted)
		p->single_quoted = !p->single_quoted;
	if (c == '\"' && !p->single_quoted)
		p->double_quoted = !p->double_quoted;
}

/*
Appends a char to a string. If the string doesn't exist yet,
makes a new string with the char as only content.
Frees the passed string.
*/
char	*append_char(char *string, char c)
{
	char	*result;
	int		i;

	if (!string)
	{
		result = ft_calloc(2, sizeof(char));
		result[0] = c;
		return (result);
	}
	result = ft_calloc(ft_strlen(string) + 2, sizeof(char));
	i = 0;
	while (string[i])
	{
		result[i] = string[i];
		i++;
	}
	result[i] = c;
	free (string);
	return (result);
}


/*
Adds a new node to the end of the list with the content <lexeme> if
lexeme has content.
If the lexeme represents an operator, sets bool operator to true,
if not, to false.
Always returns NULL, this is to reset lexeme in the calling function.
*/
char	*add_tokennode(t_par *p, char *lexeme)
{
	t_tok	*token;

	if (lexeme)
	{
		token = malloc(1 * sizeof(t_tok));
		token->lexeme = lexeme;
		token->operator = p->prev_chartype == operator;
		token->expansion = p->prev_chartype == dollar;
		ft_lstadd_back(&p->tokenlist, ft_lstnew(token));
	}
	return (NULL);
}

/*
lexeme will be NULL here if the tokenchange occured due to a whitespace.
If lexeme isn't NULL, save it in a node and NULL it afterwards to pass it
as NULL to append_chartostr which will alloc for it again - thus becoming
the next lexeme's address. Unless it's whitespace, which doesn't need to be
output - unless quoted etc.
*/
char	*change_tokennode(t_par *p, char *lexeme, char c)
{
	lexeme = add_tokennode(p, lexeme);
	if (is_tokenpart(p, c))
		lexeme = append_char(lexeme, c);
	return (lexeme);
}
