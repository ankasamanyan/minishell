#include "../../include/minishell.h"

void	shutdown(t_data *data)
{
	free2d_char(data->env);
	del_tokenlist(data->parsing_struct.tokenlist);
	del_cmdlist(data->cmd_list);
	del_explist(data->exp_list);
	free(data->parsing_struct.input);
	//free(data->shell_lvl);
}

void	free2d_char(char **array)
{
	int		i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/*
Cmdlist, inputlist and outputlist don't free any strings.
"Their" strings only point to the allocs in tokenlist.
All char * are freed in this function.
*/
void	del_tokenlist(t_list *list)
{
	t_list		*temp1;
	t_list		*temp2;
	t_tok		*token;

	temp1 = list;
	while (temp1)
	{
		if (temp1->content)
		{
			token = temp1->content;
			if (token->lexeme)
				free(token->lexeme);
			free(token);
		}
		temp2 = temp1;
		temp1 = temp1->next;
		free(temp2);
	}
}

void	del_cmdlist(t_list *list)
{
	t_list		*temp;
	t_cmd		*cmd;

	while (list)
	{
		cmd = list->content;
		if (cmd->cmd_arr)
			free(cmd->cmd_arr);
		del_pairlist(cmd->inputlist);
		del_pairlist(cmd->outputlist);
		free(cmd);
		temp = list;
		list = list->next;
		free(temp);
	}
}

void	del_pairlist(t_list *list)
{
	t_list		*temp;
	t_pair		*pair;

	while (list)
	{
		pair = list->content;
		free(pair);
		temp = list;
		list = list->next;
		free(temp);
	}
}
