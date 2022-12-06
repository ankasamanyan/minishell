#include "../../include/minishell.h"

bool	export(t_cmd *cmdnode)
{
	char	**env_clone;

	//syntaxcheck
	env_clone = clone_env(cmdnode->data);
}

char	**clone_env(t_data *data)
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
