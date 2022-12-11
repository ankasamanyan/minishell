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
	// while (data->env[i])
	// {
	// 	printf("%s\n", data->env[i]);
	// 	i++;
	// }
	return (false);
}

void	env_builtin(t_cmd *cmdnode)
{
	int		i;
	t_data	*data;

	// write(2, ft_itoa(cmdnode->fd_out), ft_strlen(ft_itoa(cmdnode->fd_out)));
	// write(2, "\n", 1);
	data = cmdnode->data;
	if (cmdnode->cmd_arr[1])
	{
		return ; //ERROR MESSAGEEEEEEEEEEEE
	}
	if (!data->env)
		return ;
	i = 0;
	while (data->env[i])
	{
		write(cmdnode->fd_out, data->env[i], ft_strlen(data->env[i]));
		write(cmdnode->fd_out, "\n", 1);
		// printf("%s\n", data->env[i]);
		i++;
	}
	//return (false);
}

/*
env is the list of export variables that are declared and defined.
E.g. "export i=0" will result in i being added to env.
"export i" will not result in i being added to env (only to export).
This function (re)builds env from the export list.
It is called at the start of minishell to create the starting env version.
It is also called whenever export makes a modification to the export list.
*/
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
			string = ft_strjoin(expnode->name, "=");
			data->env = append_string(data->env,
					ft_strjoin(string, expnode->value));
			free (string);
		}
		temp = temp->next;
	}
}
