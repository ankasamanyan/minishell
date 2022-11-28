#include "../../include/minishell.h"

/*
-	Cycles through the entire command (input)
-	Checks quotation and stores status in struct for getchartype
-	gets chartype of current char
-	if chartype is incompatible to previous char
	(not same chartype or previous charytpe wasn't init)
	-	Builds a new token and stores what was read so far (lexeme) in it
	-	Resets lexeme
-	Always stores current char in lexeme - unless it is a whitespace
-	Updates prev chartype to the current char's type
-	Final token creation after all the input has been read.
*/
void	lexer(t_par *p)
{
	int				i;
	char			*lexeme;
	t_chartype		curr_chartype;

	i = 0;
	lexeme = NULL;
	while (p->input[i])
	{
		check_quotation(p, p->input[i]);
		curr_chartype = get_chartype(p, p->input[i]);
		if (!(p->prev_chartype & (curr_chartype | init_lex)))
		{
			add_tokennode(p, lexeme);
			free(lexeme);
			lexeme = NULL;
		}
		if (curr_chartype != whitespace)
			lexeme = append_char(lexeme, p->input[i]);
		p->prev_chartype = curr_chartype;
		i++;
	}
	add_tokennode(p, lexeme);
	free(lexeme);
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
Creates a t_tok struct and fills it with the data from lexer.
Adds a node to a standard libft t_list struct whose content is the created
t_tok struct.
*/
void	add_tokennode(t_par *p, char *lexeme)
{
	t_tok	*token;

	if (!lexeme)
		return ;
	token = malloc(1 * sizeof(t_tok));
	token->lexeme = ft_strdup(lexeme);
	token->operator = p->prev_chartype == operator;
	ft_lstadd_back(&p->tokenlist, ft_lstnew(token));
}

/*
Only checks for mode adapting, not whether the quote should
get printed.
If the other quotation mark is not active: flips status of
detected quotation mark.
*/
void	check_quotation(t_par *p, char c)
{
	if (c == '\'' && !p->double_quoted)
		p->single_quoted = !p->single_quoted;
	if (c == '\"' && !p->single_quoted)
		p->double_quoted = !p->double_quoted;
}
