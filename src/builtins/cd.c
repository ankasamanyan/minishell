#include "../../include/minishell.h"

/*
NULLs cwd because it has to be initialized before being passed to getcwd.
Also serves as a check for whether there was a malloc that we have to free:
Outputpath is not always malloc'd.
If inputpath is NULL, that means the command was just "cd" and that goes to
homedir.
If inputpath starts with a '/', that means we have an absolute path, so inputpath
is exactly where we want to try to go.
Else, we have to build an absolute path from the relative path that was given:
'current directory' + '/' + 'inputpath'.
*/
void	cd(t_data *data, char *inputpath)
{
	char	*outputpath;
	char	*cwd;
	char	*temp;

	cwd = NULL;
	if (!inputpath)
		outputpath = get_homedir(data->env);
	else if (inputpath[0] == '/')
		outputpath = inputpath;
	else
	{
		cwd = getcwd(cwd, 0);
		temp = ft_strjoin(cwd, "/");
		outputpath = ft_strjoin(temp, inputpath);
	}
	if (chdir(outputpath))
		msg_bltnfail("cd", inputpath, E_NOFILDIR);
	if (cwd)
	{
		free(cwd);
		free(temp);
		free(outputpath);
	}
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
