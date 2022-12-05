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
bool	is_quotationmark(char c)
{
	return (c == '\"' || c == '\'');
}
