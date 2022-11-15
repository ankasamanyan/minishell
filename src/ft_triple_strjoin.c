#include "../include/minishell.h"

char	*ft_triple_strjoin(char *first, char *second, char *third)
{
	char	*temp;
	char	*aus;

	temp = ft_strjoin(first, second);
	aus = ft_strjoin(temp, third);
	free(temp);
	return (aus);
}
