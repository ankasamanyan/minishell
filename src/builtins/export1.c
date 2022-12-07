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
	int		i;
	t_exp	*expnode;
	int		len_name;

	if (!cmdnode->cmd_arr[1])
		return (print_export(cmdnode->data->exp_list), false);
	if (cmdnode->cmd_arr[1][0] == '-')
		return (msg_error("export", cmdnode->cmd_arr[1], E_INVALOPT), true);
	i = 1;
	while (cmdnode->cmd_arr[i])
	{
		expnode = malloc(1 * sizeof(t_exp));
		len_name = ft_strchr(cmdnode->cmd_arr[i], '=') - cmdnode->cmd_arr[i];
		expnode->name = ft_substr(cmdnode->cmd_arr[i], 0, len_name);
		if (has_invalidformat(expnode->name))
		{
			free(expnode->name);
			free(expnode);
			i++;
			continue ;
		}
		expnode->value = ft_substr(cmdnode->cmd_arr[i], len_name + 1,
				ft_strlen(cmdnode->cmd_arr[i]));
		expnode->rank = -1;
		printf("name:%s\n", expnode->name);
		printf("value:%s\n", expnode->value);
		ft_lstadd_back(&cmdnode->data->exp_list, ft_lstnew(expnode));
		i++;
	}
	set_order(cmdnode->data->exp_list);
	return (false);
}

bool	has_invalidformat(char *string)
{
	int		i;

	i = 0;
	if (ft_isdigit(string[0]))
		return (msg_error("export", string, E_NOTVALID), true);
	while (string[i])
	{
		if (!ft_isalnum(string[i]) && string[i] != '_')
			return (msg_error("export", string, E_NOTVALID), true);
		i++;
	}
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
		printf("declare -x %s=\"%s\"\n", expnode->name, expnode->value);
		i++;
	}
}
