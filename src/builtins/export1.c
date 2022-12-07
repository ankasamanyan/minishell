#include "../../include/minishell.h"

/*
For now, is only creating the export shismshmang if the function is called.
That prolly should be changed later and moved to init to be more structured.

export a=3 b =2 c=3
- 	a and c will work, it will not process b and give error ` =2': not a valid
	identifier b will only get declared. So each string represents the var name
	until either = or end of token (0, metachar whaeva)
-	bash-3.2$ export "a      =b"
	bash: export: `a      =b': not a valid identifier
-	bash-3.2$ export "a|=b"
	bash: export: `a|=b': not a valid identifier
-	bash-3.2$ export "a<=b"
	bash: export: `a<=b': not a valid identifier
-	Gonna go with: no metachars allowed except ofc '='

*/
bool	export(t_cmd *cmdnode)
{
	//char	**env_clone;

	//syntaxcheck, gotta do it per cmdarrpos tho, cause invalid ones get
	//skipped and dont terminate whole shmismshmang
	if (!cmdnode->cmd_arr[1])
		return (print_export(cmdnode->data->exp_list), false);
	if (cmdnode->cmd_arr[1][0] == '-')
		return (msg_error("export", cmdnode->cmd_arr[1], E_INVALOPT), true);
	build_exportlist(cmdnode->data);
	print_export(cmdnode->data->exp_list);
	return (false);
}

void	print_export(t_list *list)
{
	int			i;
	t_list		*temp;
	t_exp		*expnode;

	i = 0;
	while (i < ft_lstsize(list))
	{
		temp = list;
		expnode = temp->content;
		while (expnode->rank != i)
		{
			temp = temp->next;
			expnode = temp->content;
		}
		expnode = temp->content;
		printf("%i:%s\n", i, expnode->name);
		i++;
	}
}
