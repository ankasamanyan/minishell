/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_util_general.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:05:49 by wmardin           #+#    #+#             */
/*   Updated: 2022/12/20 14:05:49 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Appends a char to a string. If the string doesn't exist yet,
makes a new string with the char as only content.
Has an extra test for !string and char == 0 to prevent the resulting
string from being 00. If the char is 0, only callocs for the 0 byte,
so the resulting string is 0.
Frees the passed string.
Danger! The intended use case is narrow. You might end up freeing stuff
you intended to keep.
It should mostly only be used for one and the same string.
Ok:				string_a = appendchar(string_a, char c);
Probably bad:	string_b = appendchar(string_a, char c);
It won't leak, but string_a is lost.
*/
char	*append_char(char *string, char c)
{
	char	*result;
	int		i;

	if (!string && c == 0)
		return (ft_calloc(1, sizeof(char)));
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
Danger! The intended use case is narrow. You might end up freeing stuff
you intended to keep.
It should mostly only be used for one and the same array.
Ok:				array_a = append_string(array_a, string);
Probably bad:	array_b = append_string(array_a, string);
It won't leak, but array_a is lost.
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
