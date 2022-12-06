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
-	init order to -1 to show that it has not been evaluated.
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
		expnode->order = -1;
		ft_lstadd_back(&data->exp_list, ft_lstnew(expnode));
		i++;
	}
	
}
