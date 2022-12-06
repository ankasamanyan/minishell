#include "../../include/minishell.h"

/*
For now, is only creating the export shismshmang if the function is called.
That prolly should be changed later and moved to init to be more structured.
*/
bool	export(t_cmd *cmdnode)
{
	char	**env_clone;

	//syntaxcheck
	if (!cmdnode->cmd_arr[1])
		return (print_export(cmdnode->data), false);
	if (cmdnode->cmd_arr[1][0] == '-')
		return (msg_error("export", cmdnode->cmd_arr[1], E_INVALOPT), true);
	replace_env(cmdnode->data);
}

void	replace_env(t_data *data)
{
	int		i;
	char	**env_clone;

	if (!data->env)
		return (NULL);
	i = 0;
	env_clone = NULL;
	while (data->env[i])
		env_clone = append_string(env_clone, data->env[i]);
	data->env = env_clone;
}

/* t_list	*build_exportlist(t_data *data)
{
	int		i;
	t_exp	*expnode;
	t_list	*list;

	i = 0;
	while (data->env[i])
	{

		expnode = malloc(1 * sizeof(t_exp));
		expnode.
	}
} */
