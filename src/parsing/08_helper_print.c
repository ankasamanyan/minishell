#include "../../include/minishell.h"

void	print_tokenlist(t_list *list)
{
	t_list		*temp;
	t_tok		*token;

	printf("printing tokenlist:\n");
	temp = list;
	while (temp)
	{
		token = temp->content;
		if (token->operator)
			printf("operator:`%s'\n", token->lexeme);
		else
			printf("word:`%s'\n", token->lexeme);
		temp = temp->next;
	}
}

void	print_cmdlist(t_list *list)
{
	t_list			*temp;
	int				i;

	i = 0;
	temp = list;
	while (temp)
	{
		printf("__________COMMAND NODE %i__________\n", i);
		if (((t_cmd *)(temp->content))->builtin)
			printf("eto builtin\n");
		else
			printf("niet builtin\n");
		i++;
		print_cmd_arr(temp);
		print_inputlist(temp);
		print_outputlist(temp);
	temp = temp->next;
	}
}

void	print_cmd_arr(t_list *node)
{
	int		i;
	char	**array;

	i = 0;
	array = ((t_cmd *)(node->content))->cmd_arr;
	if (!array)
	{
		printf("___no commands___\n");
		return ;
	}
	printf("___cmd_arr___\n");
	while (array[i])
	{
		printf("cmd_arr[%i]:%s\n", i, array[i]); //problemread
		i++;
	}
}

/*
Could make a single function for in and out and pass more args to it.
Maybe later if we actually keep using and adapting this.
*/
void	print_inputlist(t_list *node)
{
	t_cmd		*cmd;
	t_list		*inlist;
	t_pair		*pair;

	cmd = node->content;
	inlist = cmd->inputlist;
	if (inlist)
		printf("___input redir___\n");
	else
		printf("___no input redir___\n");
	while (inlist)
	{
		pair = inlist->content;
		ft_printf("string:'%s'\n", pair->string);
		if (pair->doublebracket)
			ft_printf("doublebracket: yes\n");
		else
			ft_printf("doublebracket: no\n");
		inlist = inlist->next;
	}
}

void	print_outputlist(t_list *node)
{
	t_cmd		*cmd;
	t_list		*outlist;
	t_pair		*pair;

	cmd = node->content;
	outlist = cmd->outputlist;
	if (outlist)
		printf("___output redir___\n");
	else
		printf("___no output redir___\n");
	while (outlist)
	{
		pair = outlist->content;
		ft_printf("string:'%s'\n", pair->string);
		if (pair->doublebracket)
			ft_printf("doublebracket: yes\n");
		else
			ft_printf("doublebracket: no\n");
		outlist = outlist->next;
	}
}
