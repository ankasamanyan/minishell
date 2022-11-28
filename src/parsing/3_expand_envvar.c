#include "../../include/minishell.h"

void	expand_envvar(t_par *p)
{
	t_list	*temp;
	t_tok	*token;
	char	*tempstring;

	temp = p->tokenlist;
	while (temp)
	{
		token = temp->content;
		while (get_dollarposition(p, token->lexeme) != -1)
		{
			tempstring = token->lexeme;
			token->lexeme = replace_dollar(p, token->lexeme);
			free(tempstring);
		}
		temp = temp->next;
	}
}

/*
Returns the first actionable '$' defined as:
-	Not single quoted
-	Not at the end of a token, i.e. followed by at least one char that is
	-	not 0
	-	not a metachar
Only have to test for "not 0" because this function gets
called after lexing: That means a metachar will aready have resulted
in token delimitation.

Sets doublequoted to false in the if clause before returning because this
return can happen while doublequoted is still true. Doesn't have to do it for
singlequoted because that always gets to the closing quote. The case
of unclosed quotes isn't handled because it would have already thrown an
error during syntax check.
*/
int	get_dollarposition(t_par *p, char *input)
{
	int		i;

	i = -1;
	while (input[++i])
	{
		check_quotation(p, input[i]);
		if (p->single_quoted)
			continue ;
		if (input[i] == '$' && input[i + 1])
		{
			p->double_quoted = false;
			return (i);
		}
	}
	return (-1);
}

/*
test cases:
echo$""

echo$"" asdf
asdf
echo$""test
echotest: command not found
echo$"sdfsd"
echosdfsd: command not found
*/
/*
The subject only deals with the following var expansion cases:
-	Environment var expansion
-	$?

There are 2 cases For an actionable $:
-	$ immediately followed by a quotation mark
	-	Remove $, keep what is inside quotes
	-	do not attempt expansion
-	$ immediately followed by non metachar and non quotation mark
	- 	remove $ and all following chars up to next metachar or
		quotation mark.
	-	attempt expansion using the removed chars minus the $
	-	if expansion fails: write nothing.
	-	if expansion succeeds: write what was found

Splits the input string into 3 parts:
-	string_a: Start of string up to and including the last char before the
	first valid $.
-	string_b: Starts at first char after the $ up to but not including the
	first 0 or quotationmark.
-	string_c: Starts at and includes the 0 or quotationmark that delimited string_b
	and goes to the end of the string (which will ofc be the same char in
	case of 0).
	ft_strlen(lexeme) will always be too long, but it doesn't matter because
	ft_substr will just terminate at end of string. Only important that it
	doesn't terminate too soon.
-	Keeps string_a and string_c
-	Searches for the contents of string_b in at the start of each position of env.
-	If found, takes the substring of that env part. Starts strlen of string_b + 1
	in order to skip the identifier string and the equal sign at start of env
	position.
-	Then just mashes the strings back together in string a
-	Frees strings b and c; lexeme gets freed in calling function
*/
char	*replace_dollar(t_par *p, char *lexeme)
{
	int		i;
	int		dollar;

	dollar = get_dollarposition(p, lexeme);
	if (is_quotationmark(lexeme[dollar + 1]))
		return (del_singlechar(lexeme, dollar));
	i = dollar;
	p->str_a = ft_substr(lexeme, 0, i);
	while (lexeme[i] && !is_quotationmark(lexeme[i]))
		i++;
	p->str_b = ft_substr(lexeme, dollar + 1, i - dollar - 1);
	p->str_c = ft_substr(lexeme, i, ft_strlen(lexeme));
	findandexpand(p);
	p->str_a = ft_strjoin(p->str_a, p->str_b);
	p->str_a = ft_strjoin(p->str_a, p->str_c);
	free(p->str_b);
	free(p->str_c);
	return (p->str_a);
}

void	findandexpand(t_par *p)
{
	int		i;

	i = 0;
	while (p->data->env[i]
		&& ft_strncmp(p->data->env[i], p->str_b, ft_strlen(p->str_b)))
		i++;
	if (!p->data->env[i])
		p->str_b = ft_calloc(sizeof(char), 1);
	else
		p->str_b = ft_substr(p->data->env[i], ft_strlen(p->str_b) + 1,
				ft_strlen(p->data->env[i]));
}

/*
Doesn't free input string because the calling functions sometimes already do it.
So absolutely needs to be freed in calling function.
*/
char	*del_singlechar(char *string, int del_pos)
{
	char	*result;

	string[del_pos] = 0;
	result = ft_strjoin(string, string + del_pos + 1);
	return (result);
}
