#include "../../include/minishell.h"

/*
-	len_name is the int length of the name (the part of the env string before
	the equal sign). With that info, ft_substr can divide the string into
	the variable's name and its value.
-	init rank to -1 to show that it has not been evaluated.
	Used for alphabetizing (export with no args prints in alphabetical order)
*/
void	init_exportlistandenv(t_data *data, char **env)
{
	int		i;
	t_exp	*expnode;
	int		len_name;

	i = 0;
	data->exp_list = NULL;
	if (!env)
		return ;
	while (env[i])
	{
		expnode = malloc(1 * sizeof(t_exp));
		len_name = ft_strchr(env[i], '=') - env[i];
		expnode->name = ft_substr(env[i], 0, len_name);
		expnode->value = ft_substr(env[i], len_name + 1, ft_strlen(env[i]));
		expnode->rank = -1;
		ft_lstadd_back(&data->exp_list, ft_lstnew(expnode));
		i++;
	}
	increase_shlvl(data);
	build_env(data, data->exp_list);
	set_order(data->exp_list);
}

void	increase_shlvl(t_data *data)
{
	t_list		*node;
	t_exp		*content;
	char		*temp;

	node = get_namenode(data->exp_list, "SHLVL");
	if (!node)
		return ;
	content = node->content;
	if (!content->value)
	{
		content->value = ft_strdup("1");
		return ;
	}
	temp = content->value;
	content->value = ft_itoa(ft_atoi(content->value) + 1);
	free (temp);
}

/*
Returns the first node whose content-field "name" matches the passed
string.
*/
t_list	*get_namenode(t_list *explist, char *name)
{
	t_list	*temp;
	t_exp	*expnode;

	temp = explist;
	while (temp)
	{
		expnode = temp->content;
		if (!ft_strncmp(expnode->name, name, ft_strlen(name) + 1))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	print_export(t_cmd *cmdnode)
{
	int			i;
	t_list		*temp;
	t_exp		*expnode;

	i = 0;
	while (i < ft_lstsize(cmdnode->data->exp_list))
	{
		temp = cmdnode->data->exp_list;
		while (((t_exp *)temp->content)->rank != i)
			temp = temp->next;
		expnode = temp->content;
		ft_putstr_fd("declare -x ", cmdnode->fd_out);
		ft_putstr_fd(expnode->name, cmdnode->fd_out);
		if (expnode->value)
		{
			ft_putstr_fd("=\"", cmdnode->fd_out);
			ft_putstr_fd(expnode->value, cmdnode->fd_out);
			ft_putstr_fd("\"", cmdnode->fd_out);
		}
		ft_putstr_fd("\n", cmdnode->fd_out);
		i++;
	}
}
