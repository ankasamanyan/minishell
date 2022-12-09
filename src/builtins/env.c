#include "../../include/minishell.h"

bool	env(t_cmd *cmdnode)
{
	int		i;
	t_data	*data;

	if (cmdnode->cmd_arr[1])
		return (msg_error("env", E_MANYARG, NULL), true);
	data = cmdnode->data;
	if (!data->env)
		return (msg_error("env", "not found", NULL), true);
	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	return (false);
}

void	build_env(t_data *data, t_list *exp_list)
{
	t_list		*temp;
	char		*string;
	t_exp		*expnode;

	if (data->env)
		free2d_char(data->env);
	data->env = NULL;
	temp = exp_list;
	while (temp)
	{
		expnode = temp->content;
		if (expnode->value)
		{
			string = ft_strjoin(expnode->name, '=');
			data->env = append_string(data->env, ft_strjoin(string, expnode->value));
			free (string);
		}
		temp = temp->next;
	}
}
