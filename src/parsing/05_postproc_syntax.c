/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_postproc_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:05:36 by wmardin           #+#    #+#             */
/*   Updated: 2022/12/20 14:05:36 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Checks for invalid operatorchar combinations.
Checks for consecutive operator tokens.
MVP comment.
*/
bool	postproc_syntaxerror(t_par *p)
{
	if (has_invalidoperator(p->tokenlist))
		return (true);
	if (has_illegaloperatorsequence(p))
		return (true);
	return (false);
}

/*
Brute, but suitable for the small number of possible operators in
this subject.
*/
bool	has_invalidoperator(t_list *tokenlist)
{
	t_list		*temp;
	t_tok		*token;

	temp = tokenlist;
	while (temp)
	{
		token = temp->content;
		if (token->operator)
		{
			if (ft_strncmp(token->lexeme, "<", 2)
				&& ft_strncmp(token->lexeme, ">", 2)
				&& ft_strncmp(token->lexeme, ">>", 3)
				&& ft_strncmp(token->lexeme, "<<", 3)
				&& ft_strncmp(token->lexeme, "|", 2))
			{
				msg_senut(token->lexeme[ft_strlen(token->lexeme) - 1], false);
				return (true);
			}
		}
		temp = temp->next;
	}
	return (false);
}

/*
operators in minishell:
< > << >> |
allowed combos in bash:
<<< (herestring, but not allowed in minishell subject)
| <
| >
| >>
| <<

not allowed
<		>		<<		>>		|
______________________________________
< <		> <		<< <	>> <	| |
< >		> >		<< >	>> >
< <<	> <<	<< <<	>> <<
< >>	> >>	<< >>	>> >>
< |		> |		<< |	>> |
______________________________________
*/
bool	has_illegaloperatorsequence(t_par *p)
{
	t_list		*temp;
	t_tok		*token;
	t_tok		*next_token;

	if (!p->tokenlist)
		return (false);
	temp = p->tokenlist;
	while (temp->next)
	{
		token = temp->content;
		next_token = temp->next->content;
		if (token->operator && next_token->operator)
		{
			if (token->lexeme[0] == '|' && next_token->lexeme[0] != '|')
			{
				temp = temp->next;
				continue ;
			}
			msg_senut(next_token->lexeme[ft_strlen(next_token->lexeme) - 1], 0);
			return (true);
		}
		temp = temp->next;
	}
	return (false);
}
