#include "../../include/minishell.h"

bool	is_whitespace(char c)
{
	return (ft_strchr(" \t\n\f\r\v", c));
}

/*
Subject states that only < > | are possible operatorchars.
That means ; & ( ) are not considered operatorchars here.
*/
bool	is_operatorchar(char c)
{
	return (ft_strchr("|<>", c));
}

/*
Metachars are characters that delimit tokens.
They have 2 subgroups.
*/
bool	is_metachar(char c)
{
	return (is_whitespace(c) || is_operatorchar(c));
}

/*
Subject states that "\" does not have to be interpreted as escape char.
*/
/* bool	is_quotationmark(char c)
{
	return (c == '\"' || c == '\'');
} */

/*
Doesn't put whitespace into the token if single and double quotation are not active.
Puts singlequote into the token if doublequotation is active.
Puts doublequote into the token if singlequotation is active.
Puts everything else into the token.
*/
bool	is_tokenpart(t_par *p, char c)
{
	// dollarsign in isprintable! echo $"home" -> home (single also)
	//echo $ "home" -> $ home
	// GET RID OF THIS ENTIRELY AND ONLY USE GET CHARTYPE?
	if (!p->double_quoted && !p->single_quoted && is_whitespace(c))
		return (false);
	if (c == '\'')
		return (p->double_quoted);
	if (c == '\"')
		return (p->single_quoted);
	return (true);
}

/*
echo$""

wolf@Gogonnash:/mnt/e/42/Projects/minishell/src/parsing$ echo$"" asdf
asdf
wolf@Gogonnash:/mnt/e/42/Projects/minishell/src/parsing$ echo$""test
echotest: command not found
wolf@Gogonnash:/mnt/e/42/Projects/minishell/src/parsing$ echo$"sdfsd"
echosdfsd: command not found
wolf@Gogonnash:/mnt/e/42/Projects/minishell/src/parsing$
Probably not needed after all. maybe keep for readability / expandability
*/
bool	is_sametoken(t_par *p, t_chartype chartype)
{
	if (p->prev_chartype & (chartype | init_lex))
		return (true);
	if (p->prev_chartype == dollar && chartype == word)
		return (true);
	return (false);
}
