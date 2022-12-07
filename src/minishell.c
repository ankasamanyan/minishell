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
		// printf("%sactual code thingy: %i%s\n", YELLOW, data.exitcode, RESET);
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
	data->env = replace_env(env);
	build_exportlistfromenv(data);
	data->first_cmd = 0;
	data->first = true;
	data->cmd_count = 0;
	data->exitcode = 0;
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


/*
-	len_name is the int length of the name (the part of the env string before
	the equal sign). With that info, ft_substr can divide the string into
	the variable's name and its value.
-	init rank to -1 to show that it has not been evaluated.
	Used for alphabetizing (export with no args prints in alphabetical order)
*/
void	build_exportlistfromenv(t_data *data)
{
	int		i;
	t_exp	*expnode;
	int		len_name;

	i = 0;
	data->exp_list = NULL;
	while (data->env[i])
	{
		expnode = malloc(1 * sizeof(t_exp));
		len_name = ft_strchr(data->env[i], '=') - data->env[i];
		expnode->name = ft_substr(data->env[i], 0, len_name);
		expnode->value = ft_substr(data->env[i], len_name + 1,
				ft_strlen(data->env[i]));
		expnode->rank = -1;
		ft_lstadd_back(&data->exp_list, ft_lstnew(expnode));
		i++;
	}
	set_order(data->exp_list);
}

/*
Assigns ranks based on the alphabetical values of content.name.
while loop is terminated at lstsize -1 because the last node is
not reached during the while loop and therefore shouldn't
be included in the the while's condition count.
*/
void	set_order(t_list *list)
{
	int		i;
	t_list	*curr_ranked;
	t_list	*compare;

	reset_rank(list);
	i = 0;
	while (i < ft_lstsize(list) - 1)
	{
		curr_ranked = get_firstunranked(list);
		((t_exp *)curr_ranked->content)->rank = i;
		compare = curr_ranked->next;
		while (compare)
		{
			//printf("rank:%i\n", ((t_exp *)(compare->content))->rank);
			if (is_unrankedandprecedes(curr_ranked->content, compare->content))
			{
				((t_exp *)compare->content)->rank = i;
				((t_exp *)curr_ranked->content)->rank = -1;
				curr_ranked = compare;
			}
			compare = compare->next;
		}
		i++;
	}
	curr_ranked = get_firstunranked(list);
	((t_exp *)curr_ranked->content)->rank = i;
}

void	reset_rank(t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp)
	{
		((t_exp *)(temp->content))->rank = -1;
		temp = temp->next;
	}
}

/*
Returns the first node whose content's rank value has not yet
been modified. This corresponds to rank = -1.
*/
t_list	*get_firstunranked(t_list *list)
{
	t_list	*temp;
	t_exp	*expnode;

	temp = list;
	while (temp)
	{
		expnode = temp->content;
		if (expnode->rank == -1)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

bool	is_unrankedandprecedes(t_exp *node1, t_exp *node2)
{
	return (node2->rank == -1
		&& ft_strncmp(node1->name, node2->name,
			ft_strlen(node1->name) + 1) > 0);
}