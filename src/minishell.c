#include "../include/minishell.h"

/*
-	Minishell needs no arguments, but it won't refuse to run if given some.
	Just prints a message to inform that the arguments will not be used.
-	For the unlikely case that env is not present or doesn't contain
	the "PATH" array: aborts and sends perror msg.
-	readline returns NULL if EOF (ctrl + d) is the only content read.
	This makes bash exit, so we also exit.
-	If readline returns stuff, the parsing begins.
	Dangers:
	- leak with exit
	- a problem with cd. when PWD is unset and segfault with multiple variables
*/
void	increase_shell_lvl(char **env)
{
	char	*tmp;
	int i = 0;

	while(env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			tmp = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(env[i]+6) + 1));
			// free(env[i]);
			env[i] = tmp;
			printf("%s\n", tmp);
		}
		i++;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	int			i;
	char		*input;
	t_data		data;

	(void)argv;
	increase_shell_lvl(env);
	// printf("%s\n");
	if (argc > 1)
		write(2, E_ARGC, ft_strlen(E_ARGC));
	if (!env)
		errorexit_onlymsg("env");
	i = 0;
	// prolly not necessary here? Just let execve fail if there is no path?
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		errorexit_onlymsg("env (PATH)");
	
	while (1)
	{
		input = readline("\033[0;36mMinishell-0.2$\033[0m ");
		if (!input)
			commandexit();
		parsing(input, env, &data);
		// onexit(&data);
		free(input);
		ft_lstiter(data.cmd_list, &exec);
	}
}

//it only does that on my laptop :(((