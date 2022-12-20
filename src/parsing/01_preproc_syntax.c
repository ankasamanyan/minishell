/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_preproc_syntax.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:05:19 by wmardin           #+#    #+#             */
/*   Updated: 2022/12/20 14:05:19 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Last char may not be an operator.
First char may not be a pipe.
Quotes must be closed.
The remaining syntax check is performed after token building,
makes it smaller.
*/
bool	preproc_syntaxerror(t_par *p)
{
	char	lastchar;
	char	*temp;

	temp = p->input;
	p->input = ft_strtrim(p->input, " \t\n\f\r\v");
	free(temp);
	if (!p->input[0])
		return (true);
	lastchar = p->input[ft_strlen(p->input) - 1];
	if (p->input[0] == '|')
		return (msg_senut('|', false), true);
	if (is_operatorchar(lastchar))
		return (msg_senut('\n', false), true);
	if (has_unclosedquote(p->input))
		return (msg_senut('\n', true), true);
	return (false);
}

/*
Looks for either <'> or <"> and stores what it finds in <quote>.
Looks for the next instance of <quote> or end of string.
If end of string is encountered in this section, quote is not closed.
*/
bool	has_unclosedquote(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
				return (true);
		}
		i++;
	}
	return (false);
}
