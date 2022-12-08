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
	char	*name;

	if (!cmdnode->cmd_arr[1])
		return (print_export(cmdnode->data->exp_list), false);
	if (cmdnode->cmd_arr[1][0] == '-')
		return (msg_error("export", cmdnode->cmd_arr[1], E_INVALOPT), true);
	i = 1;
	while (cmdnode->cmd_arr[i])
	{
		name = ft_substr(cmdnode->cmd_arr[i], 0,
				ft_strchr(cmdnode->cmd_arr[i], '=') - cmdnode->cmd_arr[i]);
		if (!has_invalidformat(name))
			add_expnode(cmdnode->data->exp_list, cmdnode->cmd_arr[i]);
		free(name);
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

void	add_expnode(t_list *exp_list, char *string)
{
	int		len_name;
	t_exp	*expnode;

	expnode = malloc(1 * sizeof(t_exp));
	len_name = ft_strchr(string, '=') - string;
	expnode->name = ft_substr(string, 0, len_name);
	expnode->value = ft_substr(string, len_name + 1, ft_strlen(string));
	expnode->rank = -1;
	printf("name:%s\n", expnode->name);
	printf("value:%s\n", expnode->value);
	ft_lstadd_back(&exp_list, ft_lstnew(expnode));
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
		while (((t_exp *)temp->content)->rank != i)
			temp = temp->next;
		expnode = temp->content;
		printf("shmeclare -x %s", expnode->name);
		if (expnode->value)
			printf("=\"%s\"", expnode->value);
		printf("\n");
		i++;
	}
}
