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
*/
void	increase_shell_lvl(t_data *data,char **env)
{
	int		i;
	char	*temp;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "SHLVL=", 6))
		i++;
	if (!env[i])
		return ;
	temp = ft_itoa(ft_atoi(env[i] + 6) + 1);
	data->shell_lvl = ft_strjoin("SHLVL=", temp);
	free(temp);
	env[i] = data->shell_lvl;
	printf("%s\n", data->shell_lvl);
}

int	main(int argc, char *argv[], char *env[])
{
	int			i;
	char		*input;
	t_data		data;

	(void)argv;
	increase_shell_lvl(&data, env);
	set_signals();
	if (argc > 1)
		write(2, E_ARGC, ft_strlen(E_ARGC));
	if (!env)
		errorexit_onlymsg("env");
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		errorexit_onlymsg("env (PATH)");
	while (1)
	{
		input = readline("\033[0;36mMinishell-0.2$\033[0m ");
		add_history(input);
		if (specialcase(&data, input))
			continue ;
		init_datastruct(&data, env);
		if (parsing(input, &data))
		{
			shutdown(&data);
			continue ;
		}
		ft_lstiter(data.cmd_list, &exec);
		printf("%sactual code thingy: %i%s\n", YELLOW, data.exitcode, RESET);
		// if (data.exitcode > 255)
		// 	data.exitcode/=256;
		// printf("%sexit code thingy: %i%s\n", YELLOW, data.exitcode, RESET);
		shutdown(&data);
	}
}

/*
Function to catch edge cases such as empty input or NULL input.
Maybe expand to deal with some builtins?
*/
bool	specialcase(t_data *data, char *input)
{
	if (!input)
	{
		write(1, "exit\n", 5);
		free(data->shell_lvl);
		exit(0);
	}
	if (!input[0])
	{
		free(input);
		return (1);
	}
	return (0);
}

void	init_datastruct(t_data *data, char **env)
{
	data->cmd_list = NULL;
	data->env = env;
	data->first_cmd = 0;
	data->first = true;
	data->cmd_count = 0;
	data->exitcode = 0;
}
