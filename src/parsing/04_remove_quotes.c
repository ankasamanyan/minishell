#include "../../include/minishell.h"

/*
If result is NULL after the while loop but lexeme wasn't an empty string,
that means lexeme was a sequence of empty quotation marks.
In this case: returns an empty string instead of NULL.
*/
void	remove_quotes(t_par *p)
{
	t_list	*temp;
	t_tok	*token;
	int		i;
	char	*result;

	temp = p->tokenlist;
	while (temp)
	{
		token = temp->content;
		result = NULL;
		i = 0;
		while (token->lexeme[i])
		{
			check_quotation(p, token->lexeme[i]);
			if (!((token->lexeme[i] == '\"' && !p->single_quoted)
					|| (token->lexeme[i] == '\'' && !p->double_quoted)))
				result = append_char(result, token->lexeme[i]);
			i++;
		}
		if (!result && token->lexeme[0] != 0)
			result = ft_calloc(1, sizeof(char));
		free(token->lexeme);
		token->lexeme = result;
		temp = temp->next;
	}
}
