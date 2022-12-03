#include "../../include/minishell.h"

/*
Appends a char to a string. If the string doesn't exist yet,
makes a new string with the char as only content.
Frees the passed string.
*/
char	*append_char(char *string, char c)
{
	char	*result;
	int		i;

	if (!string)
	{
		result = ft_calloc(2, sizeof(char));
		result[0] = c;
		return (result);
	}
	result = ft_calloc(ft_strlen(string) + 2, sizeof(char));
	i = 0;
	while (string[i])
	{
		result[i] = string[i];
		i++;
	}
	result[i] = c;
	free (string);
	return (result);
}

/*
Appends a string to a string array.
If the string array doesn't exist yet,
makes a new string array with the string as only content.
Frees the passed string array.
*/
char	**append_string(char **array, char *string)
{
	char	**result;
	int		i;

	if (!array)
	{
		result = malloc(2 * sizeof(char *));
		result[0] = string;
		result[1] = NULL;
		return (result);
	}
	i = 0;
	while (array[i])
		i++;
	result = malloc((i + 2) * sizeof(char *));
	i = 0;
	while (array[i])
	{
		result[i] = array[i];
		i++;
	}
	result[i] = string;
	i++;
	result[i] = NULL;
	free(array);
	return (result);
}

/*
Deletes the char at the position "del_pos" of the string "string".
*/
char	*del_singlechar(char *string, int del_pos)
{
	char	*result;

	if (!string)
		return (NULL);
	string[del_pos] = 0;
	result = ft_strjoin(string, string + del_pos + 1);
	free(string);
	return (result);
}
