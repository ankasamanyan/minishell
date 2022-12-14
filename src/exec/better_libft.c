/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_libft.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasaman <akasaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:24:42 by akasaman          #+#    #+#             */
/*   Updated: 2022/12/21 16:24:43 by akasaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	print_2d_array(char	**arr, int fd)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i] != NULL)
		{
			ft_putstr_fd(arr[i], fd);
			if (arr[i][ft_strlen(arr[i]) - 1] != '\n')
				ft_putchar_fd('\n', fd);
			i++;
		}
	}
}

void	err_msg(char *stringy, t_data *data)
{
	data->exitcode = 1;
	write(2, "Minishell: ", 11);
	write(2, stringy, ft_strlen(stringy));
	perror(" ");
}

void	err_cmd_not_found(char *stringy, int nbr, t_data *data)
{
	write(2, "Minishell: ", 11);
	if (stringy)
		write(2, stringy, ft_strlen(stringy));
	if (nbr == 1)
	{
		data->exitcode = 127;
		write(2, ": command not found\n", 21);
	}
	else if (nbr == 2)
	{
		data->exitcode = 126;
		perror(" ");
	}
}
