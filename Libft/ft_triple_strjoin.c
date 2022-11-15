/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triple_strjoin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasaman <akasaman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:07:22 by akasaman          #+#    #+#             */
/*   Updated: 2022/09/14 19:22:13 by akasaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_triple_strjoin(char *first, char *second, char *third)
{
	char	*temp;
	char	*aus;

	temp = ft_strjoin(first, second);
	aus = ft_strjoin(temp, third);
	free(temp);
	return (aus);
}
