#include "../../include/minishell.h"

void	bltn_exit(t_data *data)
{
	del_explist(data->exp_list);
	free2d_char(data->env);
	if (data->parsing_struct.input)
		free(data->parsing_struct.input);
	rl_clear_history();
	exit(0);
}
