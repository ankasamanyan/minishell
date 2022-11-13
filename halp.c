/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   halp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankasamanyan <ankasamanyan@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 19:06:00 by akasaman          #+#    #+#             */
/*   Updated: 2022/11/13 15:02:23 by ankasamanya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(char *stringy)
{
	int		number;
	int		sign;

	number = 0;
	sign = 1;
	while (*stringy == 32 || (*stringy >= 9 && *stringy <= 13))
		stringy++;
	if (*stringy == '-')
		sign = -1;
	if (*stringy == '-' || *stringy == '+')
		stringy++;
	while (*stringy >= '0' && *stringy <= '9')
		number = number * 10 + (*stringy++ - '0');
	return (sign * number);
}

// void	*ft_calloc(size_t count, size_t size)
// {
// 	void	*ptr_thingy;
// 	size_t	counter_thingy;

// 	counter_thingy = count * size;
// 	ptr_thingy = malloc (counter_thingy);
// 	if (!ptr_thingy)
// 		return (NULL);
// 	return (memset (ptr_thingy, 0, counter_thingy));
// }

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
