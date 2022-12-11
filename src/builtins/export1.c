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
	char	*value;
	int		len_name;
	t_list	*samename;
	t_exp	*expnode;

	if (!cmdnode->cmd_arr[1])
		return (print_export(cmdnode->data->exp_list), false);
	if (cmdnode->cmd_arr[1][0] == '-')
		return (msg_error("export", cmdnode->cmd_arr[1], E_INVALOPT), true);
	i = 1;
	while (cmdnode->cmd_arr[i])
	{
		expnode = make_expnode(cmdnode->cmd_arr[i]);
		printf("make expnode: name:'%s'\n", expnode->name);
		printf("make expnode: value:'%s'\n", expnode->value);

		len_name = ft_strchr(cmdnode->cmd_arr[i], '=') - cmdnode->cmd_arr[i];
		printf("lenname:%i\n", len_name);
		name = ft_substr(cmdnode->cmd_arr[i], 0, len_name);
		if (has_invalidformat(name))
		{
			msg_err_quote("export", cmdnode->cmd_arr[i], E_NOTVALID);
			free(name);
			i++;
			continue ;
		}
		value = ft_substr(cmdnode->cmd_arr[i], len_name + 1,
				ft_strlen(cmdnode->cmd_arr[i]));
		printf("val:'%s'\n", value);
		if (!value[0])
		{
			free(value);
			value = NULL;
		}
		samename = get_samename(cmdnode->data->exp_list, name);
		if (samename)
		{
			if (value)
			{
				if (((t_exp *)samename->content)->value)
					free(((t_exp *)samename->content)->value);
				((t_exp *)samename->content)->value = value;
			}
			free(name);
		}
		else
		{
			add_expnode(cmdnode->data->exp_list, cmdnode->cmd_arr[i],
				&cmdnode->data->env);
			free(name);
			free(value);
		}
		i++;
	}
	set_order(cmdnode->data->exp_list);
	build_env(cmdnode->data, cmdnode->data->exp_list);
	return (false);
}

/*
if cases:
-	If no '=' found
-	If equal is the last char in string
*/
t_exp	*make_expnode(char *string)
{
	t_exp	*expnode;
	char	*equal_pos;

	expnode = malloc(1 * sizeof(t_exp));
	equal_pos = ft_strchr(string, '=');
	if (!equal_pos)
	{
		expnode->name = ft_strdup(string);
		expnode->value = NULL;
		return (expnode);
	}
	if (equal_pos - string == (long)ft_strlen(string) - 1)
	{
		expnode->name = ft_substr(string, 0, ft_strlen(string) - 1);
		expnode->value =ft_strdup("");
		return (expnode);
	}
	expnode->name = ft_substr(string, 0, equal_pos - string);
	expnode->value = ft_substr(string, equal_pos - string, ft_strlen(string));
	return (expnode);
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
	if (ft_isdigit(string[0]) || !string[0])
		return (true);
	while (string[i])
	{
		if (!ft_isalnum(string[i]) && string[i] != '_')
			return (true);
		i++;
	}
	return (false);
}

/*
Returns the first node whose content-field "name" matches the passed
string.
*/
t_list	*get_samename(t_list *list, char *name)
{
	t_list	*temp;
	t_exp	*expnode;

	temp = list;
	while (temp)
	{
		expnode = temp->content;
		if (!ft_strncmp(expnode->name, name, ft_strlen(name) + 1))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
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
		*env = append_string(*env, ft_strdup(string));
	expnode->rank = -1;
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
		printf("declare -x %s", expnode->name);
		if (expnode->value)
			printf("=\"%s\"", expnode->value);
		printf("\n");
		i++;
	}
}
