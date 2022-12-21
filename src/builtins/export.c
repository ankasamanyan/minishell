/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:35:41 by wmardin           #+#    #+#             */
/*   Updated: 2022/12/21 16:35:41 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
-	Rules for var names:
	-	Must be alphanumerical or '_'
	-	May not start with a number
-	Project doesn't allow flags so first char'-' generates a different error msg
	in 2nd cmd array position (the flag position).
*/
int	export(t_cmd *cmdnode)
{
	int		i;
	int		ret;

	ret = 0;
	if (!cmdnode->cmd_arr[1])
		return (print_export(cmdnode), 0);
	if (cmdnode->cmd_arr[1][0] == '-')
		return (msg_err("export", cmdnode->cmd_arr[1], E_INVALOPT), 1);
	i = 1;
	while (cmdnode->cmd_arr[i])
	{
		if (handle_expnode(cmdnode->data->exp_list,
				build_expnode(cmdnode->cmd_arr[i]), cmdnode->cmd_arr[i]))
			ret = 1;
		i++;
	}
	set_order(cmdnode->data->exp_list);
	build_env(cmdnode->data, cmdnode->data->exp_list);
	return (ret);
}

/*
if cases:
-	If no '=' found
-	If equal is the last char in string
*/
t_exp	*build_expnode(char *string)
{
	t_exp	*expnode;
	char	*equal_pos;

	expnode = malloc(1 * sizeof(t_exp));
	expnode->rank = -1;
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
		expnode->value = ft_strdup("");
		return (expnode);
	}
	expnode->name = ft_substr(string, 0, equal_pos - string);
	expnode->value = ft_substr(string, equal_pos - string + 1,
			ft_strlen(string));
	return (expnode);
}

int	handle_expnode(t_list *exp_list, t_exp *expnode, char *cmdstring)
{
	t_list		*node_samename;

	node_samename = get_namenode(exp_list, expnode->name);
	if (has_invalidformat(expnode->name))
	{
		free_expnode(expnode);
		return (msg_err_wquote("export", cmdstring, E_NOTVALID), 1);
	}
	if (node_samename && expnode->value)
	{
		if (((t_exp *)node_samename->content)->value)
			free(((t_exp *)node_samename->content)->value);
		((t_exp *)node_samename->content)->value = ft_strdup(expnode->value);
	}
	else if (!node_samename)
	{
		ft_lstadd_back(&exp_list, ft_lstnew(expnode));
		return (0);
	}
	free_expnode(expnode);
	return (0);
}

void	free_expnode(t_exp *expnode)
{
	free(expnode->name);
	if (expnode->value)
		free(expnode->value);
	free(expnode);
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
