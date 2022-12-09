#include "../../include/minishell.h"

// bool	env(t_cmd *cmdnode)
// {
// 	int		i;
// 	t_data	*data;

// 	if (cmdnode->cmd_arr[1])
// 		return (msg_error("env", E_MANYARG, NULL), true);
// 	data = cmdnode->data;
// 	if (!data->env)
// 		return (msg_error("env", "not found", NULL), true);
// 	i = 0;
// 	while (data->env[i])
// 	{
// 		printf("%s\n", data->env[i]);
// 		i++;
// 	}
// 	return (false);
// }

void	env_builtin(t_cmd *cmdnode)
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
		write(cmdnode->fd_out, data->env[1], ft_strlen(data->env[i]));
		write(cmdnode->fd_out, "\n", 2);
		// printf("%s\n", data->env[i]);
		i++;
	}
	// return (false);
}