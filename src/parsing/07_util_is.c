#include "../../include/minishell.h"

bool	is_whitespace(char c)
{
	return (ft_strchr(" \t\n\f\r\v", c));
}

/*
Subject states that only < > | are possible operatorchars.
That means ; & ( ) are not considered operatorchars here.
*/
bool	is_operatorchar(char c)
{
	return (ft_strchr("|<>", c));
}

/*
Metachars are characters that delimit tokens.
They have 2 subgroups.
*/
bool	is_metachar(char c)
{
	return (is_whitespace(c) || is_operatorchar(c));
}

/*
Subject states that "\" does not have to be interpreted as escape char.
*/
bool	is_quotationmark(char c)
{
	return (c == '\"' || c == '\'');
}

/*
echo should be handled differently because it should only be treated
as a builtin if it has flag -n. Other cases can get executed normally via
execve. See file in builtins for more.
Solution could be to implement a check for a builtin in exec part.
if builtin
	call our function
else
	execve
if builtin could be a copypaste of the test below without arr[1] part.
*/
bool	is_builtinwithflag(t_par *p)
{
	t_list		*temp;
	t_cmd		*cmdnode;

	temp = p->cmdlist;
	while (temp)
	{
		cmdnode = temp->content;
		if (!ft_strncmp("cd", cmdnode->cmd_arr[0], 3)
			|| !ft_strncmp("pwd", cmdnode->cmd_arr[0], 4)
			|| !ft_strncmp("export", cmdnode->cmd_arr[0], 7)
			|| !ft_strncmp("unset", cmdnode->cmd_arr[0], 6)
			|| !ft_strncmp("env", cmdnode->cmd_arr[0], 4)
			|| !ft_strncmp("exit", cmdnode->cmd_arr[0], 5))
		{
			if (cmdnode->cmd_arr[1])
				return (msg_bltnwithflag(cmdnode->cmd_arr[0]), true);
		}
		temp = temp->next;
	}
	return (false);
}
