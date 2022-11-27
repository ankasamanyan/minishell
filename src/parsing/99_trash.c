bool	has_illegalcombination(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i++];
			while (input[i] != quote)
				i++;
		}
		if (is_illegal_combo(input[i], input[i + 1]))
		{
			broadcast_senut(E_SENUT, input[i + 1]);
			return (true);
		}
		i++;
	}
	return (false);
}


bool	is_illegal_combo(char c, char d)
{
	if (c == '<' && (d == '>' || d == '|'))
		return (true);
	if (c == '>' && (d == '<' || d == '|'))
		return (true);
	if (c == '|' && is_operatorchar(d))
		return (true);
	return (false);
}

/*
Checks if there are more than <n_max> subsequent and
unquoted occurences of <c>.
Does not detect potentially functionally subsequent instances,
i.e. whitespace in between!
*/
bool	has_illegalrepetition(char *input, char c, int n_max)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	while (input[i])
	{
		j = 0;
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i++];
			while (input[i] != quote)
				i++;
		}
		if (input[i] == c)
		{
			j++;
			while (input[i + j] == c)
				j++;
		}
		if (j > n_max)
			return (true);
		i++;
	}
	return (false);
}

/*
Bash will not expand non empty quoted strings after $.
For the following: echo $"home"
It will just print: home
But bash will try to expand empty quotes.
For the following: echo $""
It will print an empty line because there is nothing to expand to.
Same for empty single quotes, such as: echo$''
So have to eliminate those cases.
Ok, I am a fool. Bash behaves the same. It's just that there is
nothing to print if the quote is empty...
*/
bool	is_quotewithcontent(char c, char d)
{
	if (c == '\'')
	{
		if (d == '\'')
			return (false);
		return (true);
	}
	if (c == '\"')
	{
		if (d == '\"')
			return (false);
		return (true);
	}
	return (false);
}

/*
Adds a new node to the end of the list with the content <lexeme> if
lexeme has content.
If the lexeme represents an operator, sets bool operator to true,
if not, to false.
Always returns NULL, this is to reset lexeme in the calling function.
*/
char	*add_tokennode_old(t_par *p, char *lexeme)
{
	t_tok	*token;

	if (lexeme)
	{
		token = malloc(1 * sizeof(t_tok));
		token->lexeme = lexeme;
		token->operator = p->prev_chartype == operator;
		token->expansion = p->prev_chartype ==dollar_exp;
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
	lexeme = add_tokennode(p);
	if (is_printable(c, p))
		lexeme = append_char(lexeme, c);
	return (lexeme);
}
