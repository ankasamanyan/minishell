/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:35:11 by wmardin           #+#    #+#             */
/*   Updated: 2022/12/21 16:35:11 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
-	Checks for too many arguments
-	If path is NULL, that means the command was just "cd" and that goes to
	homedir.
-	If inputpath doesn't start with a '/': it is a relative path, so an
	absolute path must be built. This had to be a separate function because I
	could only squeeze it to ca. 27 lines, but not 25. I find it less readable
	because now we have to introduce a bool that checks whether path was allocated
	or not. Could do it more elegantly with !cwd if it could remain inlined.
-	Remaining case is inputpath does start with '/': just keep it as is.
-	Calls chdir and stores result in failure *-1 because chdir returns
	either -1 or 0, but we want to return either 1 or 0.
-	If we called build_path and thus there was an alloc: free path.
-	If chdir didn't succeed and returned non zero: Print error msg.
-	Return whatever failure is.
*/
int	cd(t_cmd *cmdnode)
{
	char	*path;
	bool	alloc;
	int		failure;

	alloc = false;
	if (cmdnode->cmd_arr[1] && cmdnode->cmd_arr[2])
		return (msg_err("cd", E_MANYARG, NULL), 1);
	path = cmdnode->cmd_arr[1];
	if (!path)
		path = get_homedir(cmdnode->data->env);
	else if (path[0] != '/')
	{
		path = build_absolutepath(path);
		alloc = true;
	}
	failure = -chdir(path);
	if (failure)
		msg_err("cd", cmdnode->cmd_arr[1], E_NOFILDIR);
	else
		update_pwd(cmdnode->data);
	if (alloc)
		free(path);
	return (failure);
}

char	*get_homedir(char **env)
{
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "HOME=", 5))
		i++;
	if (!env[i])
		return (NULL);
	return (env[i] + 5);
}

char	*build_absolutepath(char *rel_path)
{
	char	*cwd;
	char	*temp;
	char	*abs_path;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	temp = ft_strjoin(cwd, "/");
	abs_path = ft_strjoin(temp, rel_path);
	free(cwd);
	free(temp);
	return (abs_path);
}

void	update_pwd(t_data *data)
{
	t_exp	*exp_pwd;
	t_exp	*exp_oldpwd;
	t_list	*pwd;
	t_list	*oldpwd;

	oldpwd = get_namenode(data->exp_list, "OLDPWD");
	pwd = get_namenode(data->exp_list, "PWD");
	if (!pwd)
		return ;
	exp_pwd = pwd->content;
	if (oldpwd)
	{
		exp_oldpwd = oldpwd->content;
		if (exp_oldpwd->value)
			free(exp_oldpwd->value);
		exp_oldpwd->value = ft_strdup(exp_pwd->value);
	}
	if (exp_pwd->value)
		free(exp_pwd->value);
	exp_pwd->value = NULL;
	exp_pwd->value = getcwd(exp_pwd->value, 0);
	build_env(data, data->exp_list);
}
