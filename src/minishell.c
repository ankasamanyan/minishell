/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasaman <akasaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:39:29 by akasaman          #+#    #+#             */
/*   Updated: 2022/12/21 16:39:30 by akasaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char		*input;
	t_data		data;

	(void)argv;
	init_datastruct(&data, env);
	smth_cedric_needs();
	if (argc > 1)
		write(2, E_ARGC, ft_strlen(E_ARGC));
	while (THE_EMPEROR_PROTECTS)
	{
		input = readline("\033[0;36mMinishell-3.2$\033[0m ");
		add_history(input);
		if (specialcase(&data, input))
			continue ;
		reset_datastruct(&data);
		if (parsing(&data, input) == 0)
			ft_lstiter(data.cmd_list, &exec);
		shutdown_parsing(&data);
	}
}

void	init_datastruct(t_data *data, char **env)
{
	data->cmd_list = NULL;
	data->exp_list = NULL;
	data->env = NULL;
	init_exportlistandenv(data, env);
	data->exitcode = 0;
	data->parsing_struct.input = NULL;
	data->big_path = NULL;
	data->pipe[READ_END] = -1;
	data->pipe[WRITE_END] = -1;
	data->first = true;
}

/*
- 	case: !input
	only ctrl + d (= EOF) was entered. Prints "exit" to STDOUT and
	exits with current exitcode.

-	case: !input[0]
	Empty line, i.e. immediately pressed enter.
*/
bool	specialcase(t_data *data, char *input)
{
	if (!input)
	{
		write(1, "exit\n", 5);
		shutdown_main(data);
		exit(data->exitcode);
	}
	if (!input[0])
	{
		free(input);
		return (true);
	}
	return (false);
}

void	reset_datastruct(t_data *data)
{
	data->cmd_list = NULL;
	data->first_cmd = 0;
	data->first = true;
	data->cmd_count = 0;
}

void	shutdown_main(t_data *data)
{
	del_explist(data->exp_list);
	free2d_char(data->env);
	if (data->parsing_struct.input)
		free(data->parsing_struct.input);
}
