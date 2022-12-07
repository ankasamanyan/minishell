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
	/* if (!cmdnode->cmd_arr[1])
		return (print_export(cmdnode->data), false); */
	if (cmdnode->cmd_arr[1][0] == '-')
		return (msg_error("export", cmdnode->cmd_arr[1], E_INVALOPT), true);
	build_exportlist(cmdnode->data);
	replace_env(cmdnode->data);
	return (false);
}

void	replace_env(t_data *data)
{
	int		i;
	char	**env_clone;

	if (!data->env)
		return ;
	i = 0;
	env_clone = NULL;
	while (data->env[i])
	{
		env_clone = append_string(env_clone, data->env[i]);
		i++;
	}
	data->env = env_clone;
}

/*
-	len_name is the int length of the name (the part of the env string before
	the equal sign). With that info, ft_substr can divide the string into
	the variable's name and its value.
-	init rank to -1 to show that it has not been evaluated.
	Used for alphabetizing which cmd export with no args does...

printf("name:%s\n", expnode->name);
printf("value:%s\n", expnode->value);
*/
void	build_exportlist(t_data *data)
{
	int		i;
	t_exp	*expnode;
	int		len_name;

	i = 0;
	while (data->env[i])
	{
		expnode = malloc(1 * sizeof(t_exp));
		len_name = ft_strchr(data->env[i], '=') - data->env[i];
		expnode->name = ft_substr(data->env[i], 0, len_name);
		expnode->value = ft_substr(data->env[i], len_name + 1,
				ft_strlen(data->env[i]));
		expnode->rank = -1;
		ft_lstadd_back(&data->exp_list, ft_lstnew(expnode));
		i++;
	}
	set_order(data->exp_list);
}

/*
Returns the first node whose content's rank value has not yet
been modified. This corresponds to rank = -1.
*/
t_list	*get_firstunranked(t_list *list)
{
	t_list	*temp;
	t_exp	*expnode;

	temp = list;
	while (temp)
	{
		expnode = temp->content;
		if (expnode->rank == -1)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

/*
Assigns ranks based on the alphabetical values of content.name.
while loop is terminated at lstsize -1 because the last node is
not reached during the while loop and therefore shouldn't
be included in the the while's condition count.
*/
void	set_order(t_list *list)
{
	int		i;
	t_list	*curr_ranked;
	t_list	*compare;
	t_exp	*content_curr_ranked;
	t_exp	*content_compare;

	i = 0;
	while (i < ft_lstsize(list) - 1)
	{
		curr_ranked = get_firstunranked(list);
		content_curr_ranked = curr_ranked->content;
		content_curr_ranked->rank = i;
		compare = curr_ranked->next;
		while (compare)
		{
			content_curr_ranked = curr_ranked->content;
			content_compare = compare->content;
			if (content_compare->rank == -1
				&& ft_strncmp(content_curr_ranked->name, content_compare->name,
					ft_strlen(content_curr_ranked->name) + 1) > 0)
			{
				content_compare->rank = i;
				content_curr_ranked->rank = -1;
				curr_ranked = compare;
			}
			compare = compare->next;
		}
		i++;
	}
	curr_ranked = get_firstunranked(list);
	content_curr_ranked = curr_ranked->content;
	content_curr_ranked->rank = i;
	print_export(list);
}

void	print_export(t_list *list)
{
	int			i;
	t_list		*temp;
	t_exp		*expnode;

	i = 0;
	//temp = list;
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
