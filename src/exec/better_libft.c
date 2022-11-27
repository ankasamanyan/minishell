#include "../../include/minishell.h"

char	*ft_triple_strjoin(char *first, char *second, char *third)
{
	char	*temp;
	char	*aus;

	temp = ft_strjoin(first, second);
	aus = ft_strjoin(temp, third);
	free(temp);
	return (aus);
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i] != NULL)
			free(array[i++]);
		free(array);
	}
}
