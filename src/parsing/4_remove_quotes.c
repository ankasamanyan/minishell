#include "../../include/minishell.h"

void	remove_quotes(t_par *p)
{
	t_list	*temp;
	t_tok	*token;
	int		i;
	char	*result;

	temp = p->tokenlist;
	result = NULL;
	while (temp)
	{
		token = temp->content;
		i = 0;
		while (token->lexeme[i])
		{
			check_quotation(p, token->lexeme[i]);
			if (!((token->lexeme[i] == '\"' && !p->single_quoted)
					|| (token->lexeme[i] == '\'' && !p->double_quoted)))
				result = append_char(result, token->lexeme[i]);
			i++;
		}
		free(token->lexeme);
		token->lexeme = result;
		result = NULL;
		temp = temp->next;
	}
}
