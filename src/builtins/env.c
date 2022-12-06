#include "../../include/minishell.h"

bool	env(t_cmd *cmdnode)
{
	int		i;
	t_data	*data;

	data = cmdnode->data;
	i = 0;
	if (!data->env)
		return (msg_error("env", "not found", NULL), true);
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	return (false);
}
