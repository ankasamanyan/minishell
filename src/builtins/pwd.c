#include "../../include/minishell.h"

void	pwd(void)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 0);
	printf("%s\n", path);
	free(path);
}
