#include "../../include/minishell.h"

void	expand_envvar(t_par *p)
{
	while (get_dollarposition(p, p->input) != -1)
		replace_dollar(p);
}

/*
Returns the first encountered legit '$' defined as:
-	Not single quoted
-	Followed by at least one char that is
	-	not 0
	-	not a metachar
Only have to test for "not 0" because this function gets
called after parsing so we are already dealing with tokens.
That means a metachar will aready have resulted in delimitation
and a $ will never be followed by a metachar, only by another
word-char or 0.

Once a legit $ is found, there are 2 cases:
-	$ immediately followed by a quotation mark (" or ')
	-	Remove $, keep what is inside quotes
	-	do not attempt expansion
-	$ immediately followed by non metachar
	- 	remove $ and all following chars up to next metachar or
		quotation marker. Here, because dealing with tokens: remove all following chars )
	-	attempt expansion using the removed chars (without $, duh)
	-	if expansion fails: keep nothing.
	-	if expansion succeeds: put that stuff


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
		if (input[i] == '$'
			&& input[i + 1])
		{
			p->double_quoted = false;
			return (i);
		}
	}
	return (-1);
}

/*
Splits the input string into 3 parts:
-	string_a: Start of string up to and including the last char before the
	first valid $.
-	string_b: Starts at first char after the $ up to but not including the
	first metachar after the dollarsign.
-	string_c: Starts at the first char after the $expansion string and goes to
	the end of the string. ft_strlen(entirestring) will always be too long,
	but it doesn't matter because ft_substr will just terminate at end of string.
	Only important that it doesn't terminate too soon.

printf("string a:'%s'\n", string_a);
	printf("string b:'%s'\n", string_b);
	printf("string c:'%s'\n", string_c);


	if (i < (int)ft_strlen(p->input) - 1)
		string_c = ft_substr(p->input, i, ft_strlen(p->input));
	else
		string_c = NULL;

		Lexer - Parser - ENV and Wildcard - Executor
*/
void	replace_dollar(t_par *p)
{
	int		i;
	int		dollar;
	char	*string_a;
	char	*string_b;
	char	*string_c;
	char	*temp;

	dollar = get_dollarposition(p, p->input);
	i = dollar;
	string_a = ft_substr(p->input, 0, i);
	while (p->input[i] && !is_metachar(p->input[i]))
		i++;
	string_b = ft_substr(p->input, dollar + 1, i - dollar - 1);
	string_c = ft_substr(p->input, i, ft_strlen(p->input));
	i = 0;
	while (p->env[i] && ft_strncmp(p->env[i], string_b, ft_strlen(string_b)))
		i++;
	if (!p->env[i])
		string_b = ft_calloc(sizeof(char), 1);
	else
		string_b = ft_substr(p->env[i], ft_strlen(string_b) + 1, ft_strlen(p->env[i]));
	temp = ft_strjoin(string_a, string_b);
	printf("string a and b:%s\n", temp);
	temp = ft_strjoin(temp, string_c);
	printf("finalstring:%s\n", temp);
	p->input = temp;
}
