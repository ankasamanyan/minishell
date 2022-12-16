#include "../include/minishell.h"

/*
-	Minishell needs no arguments, but it won't refuse to run if given some.
	Just prints a message to inform that the arguments will not be used.
-	If env is not present or doesn't contain
	the "PATH" array: aborts and sends perror msg.
-	readline returns NULL if EOF (ctrl + d) is the only content read.
	This makes bash exit, so we also exit.
-	If readline returns stuff, the parsing begins.
*/

int	main(int argc, char *argv[], char *env[])
{
	char		*input;
	t_data		data;

	(void)argv;

	init_datastruct(&data, env);
	set_signals(interactive);
	if (argc > 1)
		write(2, E_ARGC, ft_strlen(E_ARGC));
	while (1)
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
}


/*
- 	case: !input
	only ctrl + d (= EOF) was entered. Should call same builtin as "exit" but
	should also print "exit" to STDOUT.

-	case_ !input[0]
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
