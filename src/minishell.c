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
	//incorporate this into envclone

	i = 0;
	while (env[i] && ft_strncmp(env[i], "SHLVL=", 6))
		i++;
	if (!env[i])
		return ;
	temp = ft_itoa(ft_atoi(env[i] + 6) + 1);
	data->shell_lvl = ft_strjoin("SHLVL=", temp);
	free(temp);
	env[i] = data->shell_lvl;
	// printf("%s\n", data->shell_lvl);
}

int	main(int argc, char *argv[], char *env[])
{
	int			i;
	char		*input;
	t_data		data;

	(void)argv;
	//moved this stuff out of init_datastruct because this should only happen
	//upon start of minishell, not on each loop.
	//will later rename init_datastruct to reset_datastruct for the loop
	//and this stuff will get put into a new function init_datastruct.
	increase_shell_lvl(&data, env);
	data.exitcode = 0;
	data.env = replace_env(env);
	build_exportlistfromenv(&data);
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
			
		printf("%sactual code thingy: %i%s\n", YELLOW, data.exitcode, RESET);
		// printf("%sexit code thingy: %i%s\n", YELLOW, data.exitcode, RESET);
		shutdown(&data);
	}
	//doesnt make sense here ofc, has to be called by exit functions
	//but may not be called by the shutdown in the while loop
	//gonna change names to reflect the different shutdown timepoints
	del_explist(data.exp_list);
	free2d_char(data.env);
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

void	reset_datastruct(t_data *data)
{
	data->cmd_list = NULL;
	data->first_cmd = 0;
	data->first = true;
	data->cmd_count = 0;
}

/*
Using strdup to make a malloc'd copy of env so all variables are
structured the same (will be adding malloc'd ones later with export
and then would have a mix of dyn / stat alloc in the env clone).
*/
char	**replace_env(char **env)
{
	int		i;
	char	**env_clone;

	if (!env)
		return (NULL);
	i = 0;
	env_clone = NULL;
	while (env[i])
	{
		env_clone = append_string(env_clone, ft_strdup(env[i]));
		i++;
	}
	return (env_clone);
}
