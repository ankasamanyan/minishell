/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isintsize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:37:28 by wmardin           #+#    #+#             */
/*   Updated: 2022/11/12 20:41:49 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Check if the evaluated string is an accepted number format first.
Then run this function to check if the string corresponds to a number in
int range.
*/
int	ft_isintsize(char *string)
{
	int		len;

	len = ft_strlen(string);
	if (len > 11)
		return (0);
	if (string[0] == '-')
	{
		if (len == 11)
		{
			if (ft_strncmp("-2147483648", string, 69) < 0)
				return (0);
		}
		return (1);
	}
	if (len == 11)
		return (0);
	if (len == 10)
	{
		if (ft_strncmp("2147483647", string, 420) < 0)
			return (0);
	}
	return (1);
}