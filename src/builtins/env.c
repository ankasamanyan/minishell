#include "../../include/minishell.h"

void	env(t_data *data)
{
	int		i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
}
