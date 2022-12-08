#include "../../include/minishell.h"

/*
-	Rules for var names:
	-	Must be alphanumerical or '_'
	-	May not start with a number
-	Project doesn't allow flags so first char'-' generates a different error msg
	in 2nd cmd array position (the flag position).

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
<<<<<<< HEAD
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
		if (!expnode->value[1])
		{
			free(expnode->value);
			expnode->value = NULL;
		}
		expnode->rank = -1;
		printf("name:%s\n", expnode->name);
		printf("value:%s\n", expnode->value);
		ft_lstadd_back(&cmdnode->data->exp_list, ft_lstnew(expnode));
=======
		name = ft_substr(cmdnode->cmd_arr[i], 0,
				ft_strchr(cmdnode->cmd_arr[i], '=') - cmdnode->cmd_arr[i]);
		if (!has_invalidformat(name))
			add_expnode(cmdnode->data->exp_list, cmdnode->cmd_arr[i],
				&cmdnode->data->env);
		else
			msg_err_quote("export", cmdnode->cmd_arr[i], E_NOTVALID);
		free(name);
>>>>>>> parsing_00
		i++;
	}
	set_order(cmdnode->data->exp_list);
	//print_export(cmdnode->data->exp_list);
	return (false);
}

/*
-	May not start with digit
-	edge case of input being "=abc" -> string would be just the 0 byte
	because there is nothing before the '='. That woul skip the while loop.
	So has to be checked for at start.
-	Must be alnum or '-'
*/
bool	has_invalidformat(char *string)
{
	int		i;

	i = 0;
<<<<<<< HEAD
	if (ft_isdigit(string[0]))
		return (msg_error("export", string, E_NOTVALID), true);
=======
	if (ft_isdigit(string[0]) || !string[0])
		return (true);
>>>>>>> parsing_00
	while (string[i])
	{
		if (!ft_isalnum(string[i]) && string[i] != '_')
			return (true);
		i++;
	}
	return (false);
}

void	add_expnode(t_list *exp_list, char *string, char ***env)
{
	int		len_name;
	t_exp	*expnode;

	expnode = malloc(1 * sizeof(t_exp));
	len_name = ft_strchr(string, '=') - string;
	expnode->name = ft_substr(string, 0, len_name);
	expnode->value = ft_substr(string, len_name + 1, ft_strlen(string));
	if (!expnode->value[0])
	{
		free(expnode->value);
		expnode->value = NULL;
	}
	else
	{
		printf("string:%s\n", string);
		*env = append_string(*env, ft_strdup(string));
	}
	expnode->rank = -1;
	ft_lstadd_back(&exp_list, ft_lstnew(expnode));
}

void	print_export(t_list *list)
{
	int			i;
	t_list		*temp;
	t_exp		*expnode;

	/* temp = list;
	while (temp)
	{
		printf("name:%s\n", ((t_exp *)(temp->content))->name);
		temp = temp->next;
	} */

	i = 0;
	while (i < ft_lstsize(list))
	{
		temp = list;
		while (((t_exp *)temp->content)->rank != i)
			temp = temp->next;
		expnode = temp->content;
<<<<<<< HEAD
		printf("declare -x %s", expnode->name);
		if (expnode->value)
			printf("=\"%s\"\n", expnode->value);
		else
			write(1, "\n", 1);
=======
		printf("shmeclare -x %s", expnode->name);
		if (expnode->value)
			printf("=\"%s\"", expnode->value);
		printf("\n");
>>>>>>> parsing_00
		i++;
	}
}
