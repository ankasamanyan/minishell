#include "../include/minishell.h"

/*
-	Minishell needs no arguments, but it won't refuse to run if given some.
	Just prints a message to inform that the arguments will not be used.
-	If env is not present or doesn't contain
	the "PATH" array: aborts and sends perror msg.
-	readline returns NULL if EOF (ctrl + d) is the only content read.
	This makes bash exit, so we also exit.
-	If readline returns stuff, the parsing begins.
	Dangers:
	- leak with exit
	- a problem with cd. when PWD is unset and segfault with multiple variables
	- starting minishell and running as first cmd "unset PATH" causes segault. not
	if running at later commands.
	- cat ctrl+ c duplicates prompt. Net chorosho

*/

int	main(int argc, char *argv[], char *env[])
{
	int			i;
	char		*input;
	t_data		data;

	(void)argv;

	init_datastruct(&data, env);
	set_signals();
	if (argc > 1)
		write(2, E_ARGC, ft_strlen(E_ARGC));
	//i think this is not necessary
	if (!env)
		errorexit_onlymsg("env");
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		errorexit_onlymsg("env (PATH)");
	//end of not necessary
	while (1)
	{
		input = readline("\033[0;36mMinishell-3.2$\033[0m ");
		add_history(input);
		if (specialcase(&data, input))
			continue ;
		reset_datastruct(&data);
		if (parsing(input, &data))
		{
			shutdown(&data);
			continue ;
		}
		ft_lstiter(data.cmd_list, &exec);
		// int j = 0;
		// while (j <= ft_lstsize(data.cmd_list))
		// {
		// 	waitpid(-1, &data.exitcode, 0);
		// 	if (data.exitcode > 255)
		// 		data.exitcode%=256;
		// 	j++;
		// }

		// printf("%sactual code thingy: %i%s\n", YELLOW, data.exitcode, RESET);
		// printf("%sexit code thingy: %i%s\n", YELLOW, data.exitcode, RESET);
		shutdown(&data);
	}
}

void	init_datastruct(t_data *data, char **env)
{
	data->env = NULL;
	init_exportlistandenv(data, env);
	data->exitcode = 0;
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
		bltn_exit(data);
		exit(0);
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
